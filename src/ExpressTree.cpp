#include "ExpressTree.h"
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

//销毁一课子树
void ExpressTree::Destroy(shared_ptr<ExpressTree>& node)
{
    node.reset();
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
