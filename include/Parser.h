#include <utility>
#include "lexer.h"

//语法分析类
class Parser
{
public:
    ~Parser() = default;
    //用Lexer初始化Parser
    //单例访问点
    static std::unique_ptr<Parser> CreateParser(std::unique_ptr<Lexer>);

private:
    //匹配记号

    //构造函数
    Parser() = default;
    Parser(std::unique_ptr<Lexer> l)
        :lexer(l){ }
    //保存本parser原始指针
    static Parser* single;
    //保存用于使用的词法分析器指针
    std::unique_ptr<Lexer> lexer;
    //保存当前Token
    Token token;
    //保存绘图的参数
    std::pair<int,int> ori;
    std::pair<int,int> scal;
    double rot;
};
