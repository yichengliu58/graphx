#include "Parser.h"
#include <sstream>
#include <iostream>
using std::cout;
std::unique_ptr<Parser> Parser::CreateParser(std::shared_ptr<Lexer> lt)
{
    //创建新的unique_ptr
	std::unique_ptr<Parser> t(nullptr);
	//分配内存
	if (Parser::single == nullptr)
	{
		Parser::single = new Parser(lt);
		t.reset(Parser::single);
	}
	return t;
}

std::shared_ptr<Lexer> Parser::GetLexer()
{
    return lexer;
}

void Parser::StartParse()
{
    std::ostringstream out;
    //先使用词法分析器分析符号
    log.push_back("开始分析符号...");
    lexer->DealFile();
    //开始递归下降分析语法
    log.push_back("开始递归分析语法...");
    //statement();
    log.push_back("语法分析结束");
    ShowLog(cout);
}

void Parser::ShowLog(std::ostream& out)
{
    for(auto s : log)
        out << s << "\n";
}

void Parser::PushLog(string& s)
{
    log.push_back(s);
}

void Parser::match(TokenType type)
{
    std::ostringstream out;
    //先获取符号
    token = lexer->GetToken();
    //匹配
    if(token.type == TokenType::Err)
    {
        out << "行号：" << token.no << " 错误类型：无法识别的符号";
        log.push_back(out.str());
    }
    else if(token.type != type)
    {
        out << "行号：" << token.no << "错误类型：未预期的符号：" << token.str;
        log.push_back(out.str());
    }
}

void Parser::statement()
{
    std::stringstream out;
    //获取第一个符号
    token = lexer->GetToken();
    //开始匹配
    switch(token.type)
    {
    case TokenType::Origin:
        //log.push_back("开始匹配Origin语句");
        origin();
        //log.push_back("离开Origin语句");
        break;
    case TokenType::Scale:
        //log.push_back("开始匹配Scale语句");
        scale();
        //log.push_back("离开Scale语句");
        break;
    case TokenType::Rot:
        //log.push_back("开始匹配Rot语句");
        rot();
        //log.push_back("离开Rot语句");
        break;
    case TokenType::For:
        //log.push_back("开始匹配For语句");
        fors();
        //log.push_back("离开For语句");
        break;
    default:
        out << "行号：" << token.no << " 错误类型：无法识别的符号";
        log.push_back(out.str());
        break;
    }
}

void Parser::origin()
{
    std::shared_ptr<ExpressTree> tmp;
    //先匹配语句关键字
    match(TokenType::Is);
    match(TokenType::Lbracket);
    //生成语法树
    tmp = expression->GetExpression();
    //后序遍历
    tmp->PostOrder(std::cout);
    //在这里调用绘图类进行表达式计算
    //...
    //...
    //继续匹配后续关键字
    match(TokenType::Comma);
    //生成第二棵语法树
    tmp = expression->GetExpression();
    //再次计算
    //...
    //...
    //完成匹配
    match(TokenType::Rbracket);
    match(TokenType::Semico);
}

void Parser::rot()
{
    match(TokenType::Is);
    std::shared_ptr<ExpressTree> tmp = expression->GetExpression();
    //...
    match(TokenType::Semico);
}

void Parser::scale()
{
    std::shared_ptr<ExpressTree> tmp;
    match(TokenType::Is);
    match(TokenType::Lbracket);
    tmp = expression->GetExpression();
    //...
    match(TokenType::Comma);
    tmp = expression->GetExpression();
    //...
    match(TokenType::Rbracket);
    match(TokenType::Semico);
}

void Parser::fors()
{
    std::shared_ptr<ExpressTree> tmp;
    match(TokenType::T);
    match(TokenType::From);
    tmp = expression->GetExpression();
    //起点坐标
    match(TokenType::To);
    tmp = expression->GetExpression();
    tmp->PostOrder(std::cout);
    //终点坐标
    match(TokenType::Step);
    tmp = expression->GetExpression();
    //步长
    match(TokenType::Draw);
    match(TokenType::Lbracket);
    tmp = expression->GetExpression();
    //左表达式
    match(TokenType::Comma);
    tmp = expression->GetExpression();
    //右表达式

    //绘制图形
    //...
    match(TokenType::Semico);
}
