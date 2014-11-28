#include "Parser.h"
static std::unique_ptr<Parser> CreateParser(std::unique_ptr<Lexer> lt)
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
