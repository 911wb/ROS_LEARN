
#include "ros/ros.h"


/*

需求：修改背景色相关参数
注意：先启动管理者设置参数之后才能够启动乌龟GUI节点


1.包含头文件
2.初始化ROS节点
3.创建节点句柄
4.创建发布者对象
5.编写发布逻辑比并发布数据

*/


int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");

	// 2.初始化ROS节点
	ros::init(argc,argv,"color");// 节点名称


	// 修改参数	
	ros::param::set("/turtlesim/background_r",0);
	ros::param::set("/turtlesim/background_g",255);
	ros::param::set("/turtlesim/background_b",0);

/*
	ros::Nodehandle nh("turtlesim");
	nh.setParam("background_r",255);
	nh.setParam("background_g",255);
	nh.setParam("background_b",255);
*/

	return 0;
}







