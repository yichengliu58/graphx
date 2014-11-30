//表达式语法树类（二叉树）
#pragma once
#include "Parser.h"
#include "lexer.h"

using std::shared_ptr;
enum Child{left,right};
class ExpressTree
{
public:
    //构造函数
    ExpressTree() = default;
    ExpressTree(Token t)
        :token(t),left(nullptr),right(nullptr){ }
    ~ExpressTree() = default;

    //产生一个节点
    static shared_ptr<ExpressTree> CreateNode(Token t);
    //产生左右孩子
    shared_ptr<ExpressTree> CreateChild(Child,Token&);
    //使用指针设置左右孩子
    void SetChild(Child,shared_ptr<ExpressTree>);

    //三种遍历
    void InOrder();
    void PostOrder();
    void PreOrder();
private:
    //当前节点的记号
    Token token;
    //左儿子
    shared_ptr<ExpressTree> left;
    //右儿子
    shared_ptr<ExpressTree> right;
};
