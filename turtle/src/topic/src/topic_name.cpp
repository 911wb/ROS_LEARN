#include "ros/ros.h"
#include "std_msgs/String.h"


/*
需求：演示不同类型的话题名称设置
    设置话题名称与命名空间

*/


int main(int argc, char *argv[])
{

    ros::init(argc, argv, "hello");
    ros::NodeHandle nh;


    // 核心：设置不同类型的话题
    // 1.全局话题类型  话题名称以/ 开头，这种情况下和节点命名以及名字没有关系
    // rosrun topic topiname __ns:=weibin   rosnode list
    ros::Publisher pub = nh.advertise<std_msgs::String>("/chat",1000);
    
    // 2.相对 无/
    // ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chat",1000);

    // 3.私有 ：/xxx/yyy/chat




    while(ros::ok())
    {



    }



    return 0;




}



