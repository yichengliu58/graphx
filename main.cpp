#include "lexer.h"
#include <iostream>

Lexer* Lexer::single = nullptr;

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
        Token t;
        std::unique_ptr<Lexer> p = Lexer::CreateLexer(path);
        p->DealFile();
        while((t = p->GetToken()).type != TokenType::Non)
            t.ToString(std::cout);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "运行时错误：" << e.what() << std::endl;
        return 1;
    }
	return 0;
}
