#include <sstream>
#include "Expression.h"

//处理最低级加减法并返回递归后的语法树
std::shared_ptr<ExpressTree> Expression::GetExpression()
{
    std::shared_ptr<ExpressTree> node;
    std::shared_ptr<ExpressTree> left;
    std::shared_ptr<ExpressTree> right;
    left = term();
    Parser::token = lexer->GetToken();
    if(Parser::token.type == TokenType::Plus || Parser::token.type == TokenType::Minus)
    {
        //初始化当前节点
        node = ExpressTree::CreateNode(Parser::token);
        right = term();
    }
    else
        lexer->PushToken(Parser::token);
    node->SetChild(Child::left,left);
    node->SetChild(Child::right,right);
    return node;
}

//自己的匹配
void Expression::match(TokenType type)
{
    std::ostringstream out;
    //先获取符号
    Parser::token = lexer->GetToken();
    //匹配
    if(Parser::token.type == TokenType::Err)
    {
        out << "行号：" << Parser::token.no << " 错误类型：无法识别的符号";
        Parser::log.push_back(out.str());
    }
    else if(Parser::token.type != type)
    {
        out << "行号：" << Parser::token.no << "错误类型：未预期的符号：" << Parser::token.str;
        Parser::log.push_back(out.str());
    }
}

//处理常数、参数、函数、以及括号表达式
std::shared_ptr<ExpressTree> Expression::atom()
{
    std::shared_ptr<ExpressTree> node;
    Parser::token = lexer->GetToken();
    switch(Parser::token.type)
    {
    //最高级匹配（常数、参数、函数等）并创建一个树节点
    case TokenType::Const:
    case TokenType::T:
        node = ExpressTree::CreateNode(Parser::token);
        return node;
    case TokenType::Func:
        //如果是函数则继续匹配
        match(TokenType::Lbracket);
        //产生本节点
        node = std::make_shared<ExpressTree>(Parser::token);
        //产生本节点左儿子（即函数内参数子树）
        node->SetChild(Child::left,GetExpression());
        //匹配右括号
        match(TokenType::Rbracket);
        return node;
    case TokenType::Lbracket:
        //匹配左括号内表达式
        node = GetExpression();
        match(TokenType::Rbracket);
        return node;
    default:
        std::ostringstream out;
        out << "行号：" << Parser::token.no << " 错误类型：未预期的符号";
        Parser::log.push_back(out.str());
        return nullptr;
    }
}

//处理乘方运算
std::shared_ptr<ExpressTree> Expression::component()
{
    //产生当前节点
    std::shared_ptr<ExpressTree> node;
    //产生左右儿子
    std::shared_ptr<ExpressTree> left;
    std::shared_ptr<ExpressTree> right;
    //给左儿子赋值
    left = atom();
    //获取下一个记号
    Parser::token = lexer->GetToken();
    //如果下一个记号符合乘方运算则继续匹配
    if(Parser::token.type == TokenType::Power)
        //继续递归一次实现右结合
        right = component();
    //不是则将符号返回给Lexer缓冲区
    else
        lexer->PushToken(Parser::token);
    //设置左右儿子
    node->SetChild(Child::left,left);
    node->SetChild(Child::right,right);
    return node;
}

//处理一元加减法
std::shared_ptr<ExpressTree> Expression::factor()
{
    std::shared_ptr<ExpressTree> node;
    Parser::token = lexer->GetToken();
    //一元加
    if(Parser::token.type == TokenType::Plus)
        node = factor();
    //一元减
    else if(Parser::token.type == TokenType::Minus)
        node->SetChild(Child::right,factor());
    //匹配其他非终结符
    else
        node = component();
    return node;
}

//处理普通乘除法
std::shared_ptr<ExpressTree> Expression::term()
{
    std::shared_ptr<ExpressTree> node;
    std::shared_ptr<ExpressTree> left;
    std::shared_ptr<ExpressTree> right;
    //先把左操作数匹配
    left = factor();
    //匹配操作符
    Parser::token = lexer->GetToken();
    if(Parser::token.type == TokenType::Mul || Parser::token.type == TokenType::Div)
    {
        //初始化当前节点
        node = ExpressTree::CreateNode(Parser::token);
        //并且继续匹配右操作符
        right = factor();
    }
    //不是就把符号返回
    else
        lexer->PushToken(Parser::token);
    //设置儿子们
    node->SetChild(Child::left,left);
    node->SetChild(Child::right,right);
    return node;
}




