
#include "ros/ros.h"
#include "turtlesim/Spawn.h"

/*

需求：向服务端发送请求，生成乌龟
话题：/spawn
消息:/turtlesim/spawn


*/


int main(int argc, char* argv[])
{
	setlocale(LC_ALL,"");

	// 1.包含头文件
	// 2.初始化ros节点
	ros::init(argc, argv, "service_call");
	// 3.创建节点句柄
	ros::NodeHandle nh;

	// 4.创建一个客户端对象
	ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
	// 5.处理请求并产生响应
	turtlesim::Spawn spawn;
	spawn.request.x = 1.0;
	spawn.request.y = 1.0;
	// 乌龟朝向
	spawn.request.theta = 3.1415/2;
	spawn.request.name = "turtle2";

	

	// 调用时机：客户端发送请求之前，客户端创建对象之后
	// 调用判断服务器状态的函数,如果服务器没启动，就在此等待
	client.waitForExistence();

	// 客户端访问服务器，提交ai
	bool flag = client.call(spawn);
	

	if(flag)
	{
		ROS_INFO("响应成功,生成新的乌龟");
		ROS_INFO("新乌龟的名称: %s", spawn.response.name.c_str());
	}
	else
	{
		ROS_INFO("响应失败");
	}



	return 0;
}












