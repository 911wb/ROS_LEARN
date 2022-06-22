#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
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
    3.创建发布对象
    4.组织被发布的消息
    5.发布数据
    6.spin()

查看结果：
方法1
    rostopic list 
    rostopic echo tf_static

    header: 
        seq: 0
        stamp: 
        secs: 1643447250
        nsecs: 651216946
        frame_id: "baseCar_link"
    child_frame_id: "laser"
    transform: 
        translation: 
        x: 0.2
        y: 0.0
        z: 0.5
        rotation:
        x: 0.0
        y: 0.0
        z: 0.0
        w: 1.0
方法2：
    rviz


*/



int main(int argc, char *argv[])
{

    // 2.设置编码，节点初始化，NOdeHandle;
    setlocale(LC_ALL,"");

    ROS_INFO("----------发布方节点------------");

    ros::init(argc, argv, "static_pub");
    ros::NodeHandle nh;// 无用

    // 3.创建发布对象
    tf2_ros::StaticTransformBroadcaster pub;

    // 4.组织被发布的消息
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();

    // 两个坐标系中被参考的那一个坐标系(小车坐标系)
    tfs.header.frame_id = "baseCar_link";// fixed frame
    // 雷达坐标系
    tfs.child_frame_id = "laser";

    // 雷达坐标系到小车坐标系的位移
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;


    // 创建四元素对象
    // 向该对象设置欧拉角(单位是弧度)，这个对象可以将欧拉角转换为四元素
    tf2::Quaternion qtn;
    // 欧拉角 --> 四元数
    qtn.setRPY(0,0,0);

    // 初始化四元素
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();


    // 5.发布数据
    pub.sendTransform(tfs);

    // 6.spin()
    ros::spin();

    return 0;
}