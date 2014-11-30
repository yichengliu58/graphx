//用于计算和绘图类
#pragma once
#include "Expression.h"
#include "ExpressTree.h"
#include <memory>
//用于保存坐标信息
struct Coord
{
    double x;
    double y;
};

class Paint
{
public:
    Paint() = default;
    ~Paint() = default;
    //计算表达式的值
    double GetExprValue(std::shared_ptr<ExpressTree>);
    //绘图方法
    //...
private:
};
