#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <memory>
#include <fstream>
#include <stdexcept>

using std::string;
using std::vector;
using std::deque;

//符号类型枚举
enum TokenType
{
	//关键保留字部分
	Origin,Scale,Rot,Is,To,Step,Draw,For,From,T,
	//标点符号部分
	Semico,Lbracket,Rbracket,Comma,Plus,Minus,Mul,Div,Power,
	//函数以及常数
	Func,Const,
	//空记号出错记号
	Non,Err
};
//符号表
struct Token
{
	//记号类型
	TokenType type;
	//原始字符串
	string str;
	//数值
	double val;
	//函数指针
	double (*funPtr)(double, int);
	//默认构造函数
	Token() = default;
	//重载构造函数
	Token(TokenType t, string s, double d, double f(double, int))
		:type(t), str(s), val(d), funPtr(f){ }
    //默认拷贝构造函数
    Token(const Token&) = default;

    void ToString(std::ostream& out)
    {
        out << "type: " << type << "    str: " << str << "  val: " << val << "\n";
    }
};

//词法分析类
class Lexer
{
public:
    //析构时关闭文件
	~Lexer()
	{
	    stream.close();
	}
	//单例访问点
	static std::unique_ptr<Lexer> CreateLexer(string&);
    //处理整个文件
    void DealFile();
	//处理一条语句
	void DealStatement(const string&);
    //读取当前符号缓冲一条记录
    Token GetToken();

private:
    //读取一条语句
    string getStatement();
	//工具方法
	static double func(double num, int type);
	void intobuf(string&);
	bool isstr(string&) const;
	bool isnum(string&) const;
	void upper(string&);

	//默认构造函数
    Lexer() = default;
	//单例构造函数
	Lexer(const string& path)
	{
	    stream.open(path);
	    if(!stream)
            throw std::runtime_error("打开文件失败！");
	}
	//拷贝构造函数
	Lexer(const Lexer&){ }

	//当前文件流
	std::ifstream stream;
	//当前记号序列记录
	deque<Token> tmpToken;
	//单例访问点
	static Lexer* single;

	//存储一个符号具体值的表
	const vector<Token> tokenTable
	{
		Token( TokenType::Const, "PI", 3.1415926, nullptr ),
		Token(TokenType::Const, "E", 2.71828, nullptr ),
		Token( TokenType::T, "T", 0, nullptr ),
		Token( TokenType::Func, "SIN", 1, Lexer::func),
		Token( TokenType::Func, "COS", 2, Lexer::func ),
		Token( TokenType::Func, "TAN", 3, Lexer::func ),
		Token( TokenType::Func, "LN", 4, Lexer::func ),
		Token( TokenType::Func, "EXP", 5, Lexer::func ),
		Token( TokenType::Func, "SQRT", 6, Lexer::func ),
		Token( TokenType::Origin, "ORIGIN", 0, nullptr ),
		Token( TokenType::Scale, "SCALE", 0, nullptr ),
		Token( TokenType::Rot, "ROT", 0, nullptr),
		Token( TokenType::Is, "IS", 0, nullptr ),
		Token( TokenType::For, "FOR", 0, nullptr ),
		Token( TokenType::From, "FROM", 0, nullptr ),
		Token( TokenType::To, "TO",0,nullptr ),
		Token( TokenType::Step, "STEP", 0, nullptr ),
		Token( TokenType::Draw, "DRAW",0,nullptr ),
		Token(TokenType::Semico,";",0,nullptr),
		Token(TokenType::Lbracket,"(",0,nullptr),
		Token(TokenType::Rbracket,")",0,nullptr),
		Token(TokenType::Comma,",",0,nullptr),
		Token(TokenType::Div,"/",0,nullptr),
		Token(TokenType::Plus,"+",0,nullptr),
		Token(TokenType::Minus,"-",0,nullptr),
		Token(TokenType::Mul,"*",0,nullptr),
		Token(TokenType::Power,"^",0,nullptr)
	};

};
