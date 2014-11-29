#pragma once
#include <utility>
#include "Expression.h"
#include "lexer.h"
#include "ExpressTree.h"

class Expression;
class ExpressTree;
class Lexer;
//语法分析类
class Parser
{
    //定义友元
    friend class Expression;
public:
    ~Parser() = default;
    //用Lexer初始化Parser
    //单例访问点
    static std::unique_ptr<Parser> CreateParser(std::shared_ptr<Lexer>);
    //获取词法分析器指针
    std::shared_ptr<Lexer> GetLexer();
    //开始分析源程序
    void StartParse();
    //输出日志信息
    void ShowLog(std::ostream&);
    //输入日志信息
    void PushLog(string&);
private:
    /*工具方法部分*/
    //匹配记号
    void match(TokenType type);
    //语句级别递归子程序
    void statement();
    void origin();
    void scale();
    void rot();
    void fors();
    //构造函数
    Parser() = default;
    Parser(std::shared_ptr<Lexer> lex)
        :lexer(lex){expression = nullptr;}

    /*数据字段部分*/
    //用于计算语法树的Expression对象
    std::shared_ptr<Expression> expression;
    //保存本parser原始指针
    static Parser* single;
    //保存用于使用的词法分析器指针
    std::shared_ptr<Lexer> lexer;
    //保存当前Token
    static Token token;
    //保存绘图的参数
    std::pair<int,int> ori;
    std::pair<int,int> scal;
    double rot_angle;
    //保存分析过程日志
    static std::deque<string> log;
};
