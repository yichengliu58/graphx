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


void ExpressTree::InOrder()
{
    if(this != nullptr)
    {
        this->left->InOrder();
        Parser::PushLog(token.str);
        this->right->InOrder();
    }
}

void ExpressTree::PreOrder()
{
    if(this != nullptr)
    {
        Parser::PushLog(token.ToString());
        this->left->PreOrder();
        this->right->PreOrder();
    }
}

void ExpressTree::PostOrder()
{
    if(this != nullptr)
    {
        this->left->PostOrder();
        this->right->PostOrder();
        Parser::PushLog(token.ToString());
    }
}
