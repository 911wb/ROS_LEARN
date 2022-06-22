#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"// 订阅数数据很多，把订阅的数据缓存到缓冲区
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

/*
需求：
    1.计算turtle1坐标和turtle2坐标的转换关系 T_c2c1
    2.计算角速度和线速度并发布

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

    // A.创建发布对象， 第二只乌龟的话题，<发布的消息类型>(话题，队列中最大保存的消息数，超出此阀值时，先进的先销毁)
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 100);


    // 5.转换算法
    ros::Rate rate(10);
    while(ros::ok())
    {

        try// 捕获异常(一直循环出现错误也不退出循环)，直到正常
        {
            
            // -------------- 1.计算turtle1坐标和turtle2坐标的转换关系 T_c2c1 --------------
            // 通过turtle1和turtle2到world的关系(T_wc1 、T_wc2)
            // Pc1 = T_c1w * Pw  Pc2 = T_c2w * Pw --> Pc2 = T_c2w *  T_wc1 * Pc1
            // T_c2w *  T_wc1 = T_c2c1 
            // 输出目标坐标系和源坐标系，取间隔最短的两个坐标关系帧计算相对关系
            geometry_msgs::TransformStamped T21;
            // 父坐标系turtle2、子坐标系turtle1
            T21 = buffer.lookupTransform("turtle2", "turtle1", ros::Time(0) );

            ROS_INFO("t_c2c1 = (%.2f, %.2f, %.2f,)",
            T21.transform.translation.x, T21.transform.translation.y, T21.transform.translation.z);
            ROS_INFO("R_c2c1 = (%.2f, %.2f, %.2f, %.2f)",
            T21.transform.rotation.x, T21.transform.rotation.y, T21.transform.rotation.z, T21.transform.rotation.w);


            //--------------------2.计算角速度和线速度并发布----------------
            /*
            直线距离：√(x² +  y²) ， 角度Θ = arctan(y/x)
            线速度：v = 系数 * 直线距离 
            角速度：系数 * Θ

            */
            // B.速度消息
            geometry_msgs::Twist twist;
            // 线速度 ，乌龟不会横着走，飞着
            twist.linear.x = 0.8 * sqrt(pow(T21.transform.translation.x, 2) + pow(T21.transform.translation.y, 2));
            twist.angular.z = 8 * atan2(T21.transform.translation.y, T21.transform.translation.x);
            ROS_INFO("线速度= %.2f", twist.linear.x);
            ROS_INFO("角速度= %.2f", twist.angular.z);


            // C.发布
            pub.publish(twist);

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