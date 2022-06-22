#include "ros/ros.h"
#include "turtlesim/Pose.h"


/*

需求：订阅乌龟的位姿，并输出到屏幕

1.包含头文件
2.初始化ROS节点
3.创建节点句柄
4.创建订阅者对象
5.处理订阅数据
6.spin()函数

*/

// 5.处理订阅数据
// 回调函数, 参数类型是常量指针的引用 
void doPose(const turtlesim::Pose::ConstPtr& p_pose)
{

	// 通过msg获取并操作订阅到的数据
	ROS_INFO("乌龟位姿信息：坐标(%.2f,%.2f), 朝向(%.2f), 线速度(%.2f),角速度(%.2f)", p_pose->x, p_pose->y, p_pose->theta, p_pose->linear_velocity, p_pose->angular_velocity);


}



int main(int argc, char* argv[])
{
	setlocale(LC_ALL,"");
	
	// 2.初始化ROS节点
	ros::init(argc,argv,"cuihua");

	// 3.创建节点对象
	ros::NodeHandle nh;
	
	// 4.创建订阅者对象, 话题类型要一致，每次订阅到一条数据就会执行回调函数Msg
	ros::Subscriber sub = nh.subscribe("/turtle1/pose",100, doPose); 

	// 不执行return 0, 返回执行doMsg回调函数
	ros::spin();

	return 0;
}





