#include <pluginlib/class_list_macros.h>// pluginlib 宏，可以注册插件类

#include "plugin01/polygon_base.h"
#include "plugin01/polygon_plugins.h"

// step4 导出注册插件
// 插件导出类，参数：子类、父类 该文件会将两个衍生类注册为插件。
PLUGINLIB_EXPORT_CLASS(polygon_plugins_ns::sanbian, polygon_base_ns::polygon_base);
PLUGINLIB_EXPORT_CLASS(polygon_plugins_ns::sibian, polygon_base_ns::polygon_base);

// rospack plugins --attrib=plugin plugin01