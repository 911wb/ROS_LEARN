#ifndef POLYGON_BASE_H_
#define POLYGON_BASE_H_


namespace polygon_base_ns{
// step2 创建基类
// 虚基类
class polygon_base
{
protected:
    // 注意基类中必须包含无参构造
    polygon_base(){}

public:
    // notice: 纯虚函数
    // 计算周长的函数
    virtual double getlength() = 0;
    // 初始化边长的函数
    virtual void init(double side_length) = 0;

};


}






#endif