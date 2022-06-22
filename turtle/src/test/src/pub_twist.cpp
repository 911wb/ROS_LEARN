
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

/*

需求：发布速度消息
话题：/turtle1/cmd_vel
消息:geometry_msgs/Twist

rosrun turtlesim turtlesim_node

*/


int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");
	ROS_INFO("-------------消息发布方------------");
	// 2.初始化ROS节点
	ros::init(argc,argv,"mycontrol");// 节点名称

	// 创建节点句柄
	ros::NodeHandle nh;
	
	// 创建发布者对象,最多缓存10条信息
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

	// 5.编写发布逻辑比并发布数据
	// 创建被发布的消息，循环发布
	geometry_msgs::Twist twist;
	twist.linear.x = 1.0;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;	
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 1.0;

	// 发布频率, 1秒10次
	ros::Rate rate(10);
	// 设置编号
	int count = 0;
	// 加入休眠延迟第一条数据的发送，不然发送数据后，还没注册成功，就会丢失前面的数据
	ros::Duration(3).sleep();// 延迟3秒等待注册成
	while(ros::ok())// 若节点正常则返回true
	{

		// 发布对象要发布的消息
		pub.publish(twist);
		rate.sleep();

	}





	return 0;
}







