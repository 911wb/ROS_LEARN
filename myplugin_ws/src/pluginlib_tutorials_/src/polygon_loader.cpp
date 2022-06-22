
#include <pluginlib/class_loader.h>
// 表示插件加载器的引入：
#include <pluginlib_tutorials_/polygon_base.h>
 
int main(int argc, char** argv)
{

// 1.接下来就会创建一个插件加载器：
// 这里创建了一个pluginlib::ClassLoader<polygon_base::RegularPolygon>类型的插件加载器
// 第一个参数是包的名称，第二个参数是命名空间::基类名称。
pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("pluginlib_tutorials_", "polygon_base::RegularPolygon");
 
try   
  {
// 2.使用加载器来创建插件类的实例：

// 这里创建的实例为类Triangle的实例triangle，类型为基类<polygon_base::RegularPolygon>的boost::shared_ptr智能指针。
    boost::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createInstance("polygon_plugins::Triangle");// 创建子类实例

// 3.接着通过初始化函数对三角形的边长进行初始化，然后打印一下三角形的面积：
    triangle->initialize(10.0);
 
    boost::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createInstance("polygon_plugins::Square");// 创建子类实例
    square->initialize(10.0);
 
    ROS_INFO("Triangle area: %.2f", triangle->area());
    ROS_INFO("Square area: %.2f", square->area());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    ROS_ERROR("The plugin failed to load for some reason. Error: %s", ex.what());
  }
 
  return 0;
}
