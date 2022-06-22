#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"// 订阅数数据很多，把订阅的数据缓存到缓冲区
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"

/*
需求：
    1.计算sun1坐标和sun2坐标的转换关系
    2.计算son1中的某个点坐标，在sun2中的坐标值

流程：
    1.包含头文件
    2.设置编码，节点初始化，NodeHandle;
    3.创建订阅对象
    4.编写解析逻辑
    5.转换算法，需要调用tf内置实现
    
*/



int main(int argc, char *argv[])
{

    // 2.设置编码，节点初始化，NOdeHandle;
    setlocale(LC_ALL,"");

    ROS_INFO("----------订阅方节点------------");

    ros::init(argc, argv, "tfs_sub");
    ros::NodeHandle nh;

    // 3.创建订阅对象
    tf2_ros::Buffer buffer;
    // 将订阅的数据缓存到buffer
    tf2_ros::TransformListener listener(buffer);



    // 4.创建一个三维点点数据
    geometry_msgs::PointStamped pts_son1;

    // 该三维点现在属于son1坐标系(其值是在son1坐标系下观察到的)
    pts_son1.header.frame_id = "son1";
    // 
    pts_son1.header.stamp = ros::Time::now();

    // 初始化三维点坐标(实际中的坐标点是动态生成的)
    pts_son1.point.x = 1.0;
    pts_son1.point.y = 2.0;
    pts_son1.point.z = 3.0;

    // 5.转换算法
    ros::Rate rate(10);
    while(ros::ok())
    {

        try// 捕获异常(一直循环出现错误也不退出循环)，直到正常
        {
            
            // -------------- 1.计算son1坐标和son2坐标的转换关系T_21 --------------
            // 通过son1和son2到world的关系，计算出son1到son2的关系即:T_21
            // Pc1 = T_1w * Pw  Pc2 = T_2w * Pw --> Pc2 = T_2w *  T_w1 * Pc1
            // T_2w *  T_w1 = T_21 
            // 输出目标坐标系和源坐标系，取间隔最短的两个坐标关系帧计算相对关系
            geometry_msgs::TransformStamped T21;
            T21 = buffer.lookupTransform("son2", "son1", ros::Time(0) );

            ROS_INFO("t21 = (%.2f, %.2f, %.2f,)",
            T21.transform.translation.x, T21.transform.translation.y, T21.transform.translation.z);
            ROS_INFO("R21 = (%.2f, %.2f, %.2f, %.2f)",
            T21.transform.rotation.x, T21.transform.rotation.y, T21.transform.rotation.z, T21.transform.rotation.w);


            // ------------ 2.计算son1中的某个点坐标，在sun2中的坐标值 --------------
            geometry_msgs::PointStamped pts_son2;
            // 在调用转换函数之前，必须先保证发送方发送位姿T，不然报错，缓存中存放的是位姿T
            // 参数：要转换的三维点，目标坐标系, 返回转换后的结果 P_son2 = T_21 * P_son1
            pts_son2 = buffer.transform(pts_son1, "son2");// pts_son1*T21

            ROS_INFO("son1下的坐标点转换到sun2下的坐标值为:(%.2f, %.2f, %.2f)",
                pts_son2.point.x, pts_son2.point.y, pts_son2.point.z);

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