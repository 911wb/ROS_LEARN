#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

/*

rosrun tf2_ros static_transform_publisher x偏移量 y偏移量 z偏移量 z偏航角度 y俯仰角度 x翻滚角度 主坐标系 子坐标系
rosrun tf2_ros static_transform_publisher 0.2 0 0.5 0 0 0 /baselink /laser
rostopic list 
rostopic echo tf_static
需求：
    发布两个坐标系的相对关系(位姿)
流程：
    1.包含头文件
    2.设置编码，节点初始化，NOdeHandle;
    3.创建订阅对象，订阅/turtle1/pose
    4.回调函数处理订阅的位姿：将传感器坐标系下的数据转换为世界坐标系下的数据
    5.spin()

    4.组织被发布的消息
    5.发布数据

发布方：需要订阅乌龟的位姿信息，转换到世界坐标系下，并动态发布(乌龟的位姿一直在变化)
    话题：/turtle1/pose
        rostopic list
        rostopic info /turtle1/pose
        
    消息：/turtlesim/pose
        rosmsg info /turtlesim/pose


*/
std::string turtle_name;


// 输入订阅到的位姿p_pose （键盘控制节点发送消息）
void doPose(const turtlesim::Pose::ConstPtr& p_pose)
{
    // 获取位姿信息
    // a.创建发布对象，声明为静态的，每次调用回调函数都只创建使用同一个pub
    static tf2_ros::TransformBroadcaster pub;
    
    // b.组织被发布的数据
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();
    // 即将要转换到的坐标系(世界坐标系)
    tfs.header.frame_id = "world";// fixed frame

    // 动态传入
    tfs.child_frame_id = turtle_name;

    // 取出订阅到的位姿：乌龟坐标系到世界坐标系的位移
    tfs.transform.translation.x = p_pose->x;
    tfs.transform.translation.y = p_pose->y;
    tfs.transform.translation.z = 0;

    // 2D: 翻滚(沿着x) = 0， 俯仰(y) = 0 ， 偏航(z) != 0
    tf2::Quaternion qtn;
    // 取出订阅到的旋转，转换为四元素
    qtn.setRPY(0,0,p_pose->theta);
    // R: 旋转四元素
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();

    // c.发布乌龟(相机)在世界坐标系下的位姿T_wt
    pub.sendTransform(tfs);
/*
    // 乌龟到世界坐标系的转换关系(位姿)
    ROS_INFO("t_wc = (%.2f, %.2f)",tfs.transform.translation.x, tfs.transform.translation.y);
    ROS_INFO("R_wc = (%.2f, %.2f, %.2f, %.2f)", 
    tfs.transform.rotation.x,
    tfs.transform.rotation.y,
    tfs.transform.rotation.z,
    tfs.transform.rotation.w);
*/
}

int main(int argc, char *argv[])
{

    setlocale(LC_ALL,"");

    ros::init(argc, argv, "dynamic_pub");

    // 2.设置编码，节点初始化，NOdeHandle;
    ROS_INFO("----------接收并发布方节点------------");
    ros::NodeHandle nh;// 无用

    // 解析launch文件 通过args传入参数
    if( argc != 2 )
    {
        ROS_INFO("请传入一个参数");
        return 1;
    }
    else
    {
        turtle_name = argv[1];
    }



    // 3.创建订阅对象，订阅/turtle1/pose， 键盘控制节点发送消息
    // 话题名称是动态传入的 
    ros::Subscriber sub = nh.subscribe(turtle_name + "/pose", 100, doPose);

    // 6.spin()
    ros::spin();

    return 0;
}