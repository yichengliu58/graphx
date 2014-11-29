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


void ExpressTree::InOrder(std::ostream& out)
{
    if(this != nullptr)
    {
        this->left->InOrder(out);
        token.ToString(out);
        this->right->InOrder(out);
    }
}

void ExpressTree::PreOrder(std::ostream& out)
{
    if(this != nullptr)
    {
        token.ToString(out);
        this->left->PreOrder(out);
        this->right->PreOrder(out);
    }
}

void ExpressTree::PostOrder(std::ostream& out)
{
    if(this != nullptr)
    {
        this->left->PostOrder(out);
        this->right->PostOrder(out);
        token.ToString(out);
    }
}
