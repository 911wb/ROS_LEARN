#include "ros/ros.h"


int main(int argc, char *argv[])
{

    ros::init(argc,argv,"hello");
    ros::NodeHandle nh;
    // -------------使用ros::param设置参数--------------------
    // rosrun param name __ns:=weibin

    // 1.全局 /radius_A
    ros::param::set("/radius_A", 100);

    // 2.相对 /weibin/radius_A
    ros::param::set("radius_B", 100);

    // 3.私有 /weibin/hello/radius_A
    ros::param::set("~radius_C", 100);

    // -------------使用NodeHandle设置参数--------------------
    nh.setParam("/radius_nh_A", 1000);

    nh.setParam("radius_nh_B", 1000);
    // 使用该句柄，则发布话题节点为: hello/
    ros::NodeHandle nh_private("~");
    nh_private.setParam("radius_nh_C", 1000);





    return 0;




}