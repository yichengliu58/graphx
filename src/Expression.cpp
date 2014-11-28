#include <sstream>
#include "Expression.h"

std::shared_ptr<ExpressTree> Expression::GetExpression()
{
    //先获取一个记号
    Parser::token = lexer->GetToken();
    return std::make_shared<ExpressTree>(Parser::token);
}

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


