#include "Paint.h"
#include <cmath>
//double Paint::GetExprValue(std::shared_ptr<ExpressTree> root)
//{
//    if(root == nullptr)
//        return 0;
//    switch(root->token.type)
//    {
//    case TokenType::Plus:
//        return Paint::GetExprValue(root->left) + Paint::GetExprValue(root->right);
//    case TokenType::Minus:
//        return Paint::GetExprValue(root->left) - Paint::GetExprValue(root->right);
//    case TokenType::Mul:
//        return Paint::GetExprValue(root->left) * Paint::GetExprValue(root->right);
//    case TokenType::Div:
//        return Paint::GetExprValue(root->left) / Paint::GetExprValue(root->right);
//    case TokenType::Power:
//        return std::pow(Paint::GetExprValue(root->left,root->right));
//    case TokenType::Func:
//        return (Paint::GetExprValue(root->left),root->token.val);
//    case TokenType::Const:
//        return root->token.val;
//    case TokenType::T:
//        return
//    }
//}
