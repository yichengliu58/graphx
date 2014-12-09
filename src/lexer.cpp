#include "lexer.h"
#include <iostream>
#include <sstream>
double Lexer::func(double num, int type)
{
    switch(type)
    {
    case 1:
        return std::sin(num);
    case 2:
        return std::cos(num);
    case 3:
        return std::tan(num);
    case 4:
        return std::log(num);
    case 5:
        return std::exp(num);
    case 6:
        return std::sqrt(num);
    default:
        return 0;
    }
}

double Lexer::Func(double num,int type)
{
    return Lexer::func(num,type);
}

//初始化对象
std::shared_ptr<Lexer> Lexer::CreateLexer(string& filePath)
{
	//创建新的unique_ptr
	std::shared_ptr<Lexer> t(nullptr);
	//分配内存
	if (Lexer::single == nullptr)
	{
		Lexer::single = new Lexer(filePath);
		t.reset(Lexer::single);
	}
	return t;
}

void Lexer::intobuf(string& s)
{
    bool flag = false;
    //将字符串变为大写
    upper(s);
    //遍历比较
    for(auto ele : tokenTable)
        if(!ele.str.compare(s))
        {
            //调用拷贝构造函数添加
            tmpToken.push_back(Token(ele));
            tmpToken.back().no = line;
            flag = true;
            break;
        }
        //如果没有匹配成功则加入一个出错的符号
        if(!flag)
            tmpToken.push_back(Token(TokenType::Err,"error",0,nullptr,line));
}

bool Lexer::isstr(string& s) const
{
    for(char c : s)
        if(!std::isalpha(c))
            return false;
    return true;
}

bool Lexer::isnum(string& s) const
{
    bool flag = false;
    for(char c : s)
    {
        if(!std::isdigit(c))
        {
            if(c == '.' && !flag)
                flag = true;
            else
                return false;
        }
    }
    return true;
}

void Lexer::upper(string& s)
{
    auto iter = s.begin();
    for(iter;iter != s.end();iter++)
        if(*iter <= 'z' && *iter >= 'a')
            *iter = *iter + ('Z' - 'z');
}

string Lexer::getStatement()
{
    //临时变量
	string statement = "";
	//读取一条语句并删除注释以及分号
	while(stream.peek() != EOF)
	{
	    char c = stream.get();
	    //判断分号
	    if(c == ';')
        {
            statement += c;
            break;
        }
        //判断注释
        else if(c == '/')
        {
            //如果的确是注释
            if(stream.peek() == '/')
            {
                //跳到下一行
                string com;
                std::getline(stream,com);
                continue;
            }
        }
        else if(c == '-')
        {
            if(stream.peek() == '-')
            {
                string com;
                std::getline(stream,com);
                continue;
            }
        }
        statement += c;
	}
	return statement;
}

void Lexer::DealFile()
{
    string ts = "";
    while((ts = getStatement()) != "")
        DealStatement(ts);
}

void Lexer::DealStatement(const string& input)
{
    //语句号加一
    ++line;
    //处理符号
    std::istringstream is(input);
    string t;
    while(is >> t)
    {
        //判断是否有括号或者逗号，有的话需要按字符处理
        if(t.find(";") != string::npos || t.find("(") != string::npos || t.find(")") != string::npos || t.find(",") != string::npos ||
                t.find("*") != string::npos || t.find("/") != string::npos || t.find("+") != string::npos || t.find("-") != string::npos||
                t.find("p") != string::npos || t.find("P") != string::npos || t.find("e") != string::npos || t.find("E") != string::npos)
        {
            //对于其中每一个字符
            for(auto iter = t.begin();iter != t.end();iter++)
            {
                //如果是字符
                if(std::isalpha(*iter))
                {
                    string tc = "";
                    while(std::isalpha(*iter))
                    {
                        tc += *iter;
                        iter++;
                    }
                    iter--;
                    //加入符号表
                    intobuf(tc);
                }
                //数字
                else if(std::isdigit(*iter))
                {
                    string tn = "";
                    while(std::isdigit(*iter) || *iter == '.')
                    {
                        tn += *iter;
                        iter++;
                    }
                    iter--;
                    //直接添加常数
                    tmpToken.push_back(Token(TokenType::Const,tn,std::stod(tn),nullptr,line));
                }
                //其他情况是标点符号
                else
                {
                    string ts = "";
                    ts += *iter;
                    intobuf(ts);
                }
            }
        }
        //是否为常数
        else if(isnum(t))
            //添加至符号缓存
            tmpToken.push_back(Token(TokenType::Const,t,std::stod(t),nullptr,line));
        //其他情况则是纯字符
        else if(isstr(t))
            intobuf(t);
        else
            tmpToken.push_back(Token(TokenType::Err,"error",0,nullptr,line));
    }
}

Token Lexer::GetToken()
{
    //如果为空直接返回空记号
    if(tmpToken.empty())
        return Token(TokenType::Non,"none",0,nullptr);
    else
    {
        Token t(tmpToken.front());
        tmpToken.pop_front();
        return t;
    }
}

void Lexer::PushToken(Token t)
{
    tmpToken.push_front(t);
}
