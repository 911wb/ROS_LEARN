#ifndef POLYGON_PLUGINS_H_
#define POLYGON_PLUGINS_H_

#include "plugin01/polygon_base.h"

namespace polygon_plugins_ns{
// step3 创建子类
// 正三边形类，继承多边形类
class sanbian:public polygon_base_ns::polygon_base
{
private:
    double _side_length;
public:
    sanbian()
    {
        _side_length = 0.0;
    }
    virtual void init(double side_length)
    {
        this->_side_length = side_length;
    }

    virtual double getlength()
    {
        return _side_length * 3;
    }

};

// 正四边形类，继承多边形类
class sibian:public polygon_base_ns::polygon_base
{
private:
    double _side_length;
public:
    sibian()
    {
        _side_length = 0.0;
    }
    virtual void init(double side_length)
    {
        this->_side_length = side_length;
    }

    virtual double getlength()
    {
        return _side_length * 4;
    }

};



}




#endif