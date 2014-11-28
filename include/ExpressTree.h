//表达式语法树类（二叉树）
#pragma once
#include "Parser.h"

using std::shared_ptr;
enum Child{left,right};
class ExpressTree
{
public:
    ExpressTree() = default;
    ExpressTree(Token& t)
        :token(t){ }
    ~ExpressTree() = default;
    //产生左右孩子
    shared_ptr<ExpressTree> CreateChild(Child,Token&);
    //销毁子树
    void Destroy(shared_ptr<ExpressTree>&);
//    //三种遍历
//    static void InOrder(shared_ptr<ExpressTree>&);
//    static void PostOrder(shared_ptr<ExpressTree>&);
//    static void PreOrder(shared_ptr<ExpressTree>&);
private:
    //当前节点的记号
    Token token;
    //左儿子
    shared_ptr<ExpressTree> left;
    //右儿子
    shared_ptr<ExpressTree> right;
};
