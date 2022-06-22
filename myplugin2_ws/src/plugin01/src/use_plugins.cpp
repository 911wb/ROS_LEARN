#include "ros/ros.h"
#include "pluginlib/class_loader.h" // 加载器
#include "plugin01/polygon_base.h"// 基类
/*
创建类加载器，根据需求加载相关插件
    1.创建诶加载器
    2.使用类加载器实例化某个插件对象
    3.使用插件
*/


// step7  使用插件
int main()
{
    setlocale(LC_ALL,"");
    // 1.创建诶加载器，参数1:基类功能包名称 参数2:基类全限定名称
    pluginlib::ClassLoader<polygon_base_ns::polygon_base> 
        loader("plugin01", "polygon_base_ns::polygon_base");

    // 2.使用类加载器实例化某个插件对象，loader返回父类类型
    // 参数：子类类型的限定名，即插件类全限定名称，notice: 父类指针指向子类对象
    boost::shared_ptr<polygon_base_ns::polygon_base> san = loader.createInstance("polygon_plugins_ns::sanbian");

    // 3.使用插件：多态公有继承 notice:
    san->init(10);
    double length = san->getlength();
    ROS_INFO("三角形周长：%.2f", length);

    // ----------- 四边形 ----------------
    // 2.使用类加载器实例化某个插件对象，loader返回父类类型
    // 参数：子类类型的限定名，即插件类全限定名称，notice: 父类指针指向子类对象
    boost::shared_ptr<polygon_base_ns::polygon_base> si = loader.createInstance("polygon_plugins_ns::sibian");

    // 3.使用插件：多态公有继承 notice: 
    si->init(10);
    double length2 = si->getlength();
    ROS_INFO("四边形周长：%.2f", length2);


    return 0;
}
// rosrun pugins01 use_plugins