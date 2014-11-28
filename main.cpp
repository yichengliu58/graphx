#include "lexer.h"
#include "Parser.h"
#include <iostream>

Parser* Parser::single = nullptr;
Lexer* Lexer::single = nullptr;
std::size_t Lexer::line = 0;
std::deque<string> Parser::log;
Token Parser::token;

int main(int argc,char *argv[])
{
	//如果命令行参数过少产生用法信息
	if (argc < 2)
	{
		std::cout << "version" << std::endl;
		return 0;
	}
	string path = argv[1];

    try
    {
        //根据Lexer创建Parser
        std::unique_ptr<Parser> p = Parser::CreateParser(Lexer::CreateLexer(path));
        //t.ToString(std::cout);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "运行时错误：" << e.what() << std::endl;
        return 1;
    }
	return 0;
}
