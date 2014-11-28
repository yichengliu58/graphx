//用于专门处理表达式
#pragma once
#include <memory>
#include "ExpressTree.h"
#include "lexer.h"
class ExpressTree;
class Expression
{
public:
    //拷贝控制部分
    Expression(std::shared_ptr<Lexer> l)
        :lexer(l){root = nullptr;}
    ~Expression()
    {
        root.reset();
    }
    Expression(const Expression&) = default;
    //获得下一个表达式的语法树根节点
    std::shared_ptr<ExpressTree> GetExpression();
private:
    //加一个自己的match
    void match(TokenType type);
    //四个辅助方法构建语法树
    std::shared_ptr<ExpressTree> term();
    std::shared_ptr<ExpressTree> factor();
    std::shared_ptr<ExpressTree> component();
    std::shared_ptr<ExpressTree> atom();
    //用于表示当前表达式的树根
    std::shared_ptr<ExpressTree> root;
    //用于得到词法分析器指针
    std::shared_ptr<Lexer> lexer;
};
