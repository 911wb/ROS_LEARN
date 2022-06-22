#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"// 订阅数数据很多，把订阅的数据缓存到缓冲区
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"


/*
需求：
    订阅发布的坐标系转换关系，传入一个坐标点，调用tf实现转换
流程：
    1.包含头文件
    2.设置编码，节点初始化，NodeHandle;
    3.创建订阅对象
    4.组织一个坐标点数据
    5.转换算法，需要调用tf内置实现
    6.输出
*/



int main(int argc, char *argv[])
{

    // 2.设置编码，节点初始化，NOdeHandle;
    setlocale(LC_ALL,"");

    ROS_INFO("----------订阅方节点------------");

    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;

    // 3.创建订阅对象
    tf2_ros::Buffer buffer;
    // 将订阅的数据缓存到buffer
    tf2_ros::TransformListener listener(buffer);

    // 4.组织一个坐标点数据
    geometry_msgs::PointStamped pts;

    // 雷达坐标系下的三维点坐标， 必须与发布方设置的坐标系名字一致
    pts.header.frame_id = "laser";
    pts.header.stamp = ros::Time::now();
    // 实际中的坐标点是动态生成的
    pts.point.x = 2.0;
    pts.point.y = 3.0;
    pts.point.z = 5.0;

    // 添加休眠，在休眠的两秒中，足够订阅到位姿
    //ros::Duration(2).sleep();
    // 5.转换算法
    ros::Rate rate(10);
    while(ros::ok())
    {
        // 核心代码：将雷达坐标系下的三维点转换到小车坐标系下的三维点
        geometry_msgs::PointStamped pts_car;

        try// 捕获异常(一直循环出现错误也不退出循环)，直到正常
        {
            // 在调用转换函数之前，必须先保证发送方发送位姿T，不然报错，缓存中存放的是位姿T
            // 参数：要转换的三维点，转换到哪个坐标系下, 返回转换后的结果 P_car= T * P_alser
            pts_car = buffer.transform(pts, "baseCar_link");

            ROS_INFO("转换到小车坐标系后的三维点坐标:(%.2f, %.2f, %.2f)",
                pts_car.point.x, pts_car.point.y, pts_car.point.z);

            ROS_INFO("小车坐标系:%s", pts_car.header.frame_id.c_str());
        }
        catch(const std::exception& e)
        {
            ROS_INFO("异常消息%s",e.what());
        }


        rate.sleep();
        ros::spinOnce();
    }








    return 0;
}