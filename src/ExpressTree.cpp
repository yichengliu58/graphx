#include "ExpressTree.h"

shared_ptr<ExpressTree> ExpressTree::CreateNode(Token t)
{
    return std::make_shared<ExpressTree>(t);
}

//产生左右孩子
shared_ptr<ExpressTree> ExpressTree::CreateChild(Child c,Token& t)
{
    switch(c)
    {
        case Child::left:
            left = std::make_shared<ExpressTree>(t);
            return left;
        case Child::right:
            right = std::make_shared<ExpressTree>(t);
            return right;
        default:
            return nullptr;
    }
}

void ExpressTree::SetChild(Child c,shared_ptr<ExpressTree> child)
{
    if(c == Child::left)
        left = child;
    else if(c == Child::right)
        right = child;
}


//static void ExpressTree::InOrder(shared_ptr<ExpressTree>& node)
//{
//    if(node)
//    {
//        ExpressTree::InOrder(node->left);
//        node->
//        ExpressTree::InOrder(node->left);
//    }
//}
//
//static void ExpressTree::PreOrder(shared_ptr<ExpressTree>& node)
//{
//    if(node)
//    {
//        node->ShowToken(std::cout);
//        ExpressTree::PreOrder(node->left);
//        ExpressTree::PreOrder(node->right);
//    }
//}
//
//static void ExpressTree::PostOrder(shared_ptr<ExpressTree>& node)
//{
//    if(node)
//    {
//        ExpressTree::PostOrder(node->left);
//        ExpressTree::PostOrder(node->right);
//        node->ShowToken(std::cout);
//    }
//}
