#pragma once
#include<stack>
#include<string>
#include"CalcMain.h"
#include "DataManager.h"
#include "History.h"
#include "Thread_write.h"
using namespace std;
class CalcMain;
class Calculate
{
public:
	//科学计算器处理计算事件
	//str代表的是表达式框的字符串，ans代表的是结果框的字符串，btn_text代表用户点击的按钮的文本
	//c代表按钮是那种类型，比如是一般数字还是运算符
	//frame_his代表的是历史记录的对象，用来修改历史记录的显示
	//返回值是计算的结果，vec[0]表示是表达式框的文本，vec[1]表示的是结果框的文本
	vector<QString> calcEvent(QString str, QString ans, QString btn_text,
		 History *frame_his) ;
	//进制转换计算器处理计算事件
	//str代表的是显示的某个进制的字符串，btn_text代表用户点击的按钮的文本，currentIndex代表str是几进制的数
	//c代表按钮是那种类型，比如是一般数字还是运算符
	//返回值vec 0-3表示16、10、8、2进制的应当显示的结果
	vector<QString> calcConvertEvent(QString str, QString btn_text,
		char currentIndex, char c) const;
	stack<double> num;
	stack<char> op;
	void calcOnce();
	bool judgePrior(char c);
	//因为string可以直接通过下标来访问，而QString需要使用mid来访问，因此选择
	QString calcText(QString s);
	static QString deletePoint(QString s);
	static QString bigNum(QString a, QString b);
	static QString opp(QString s);
	//DataManager *dm;
	History *his{};
	Calculate(History *his);
	Calculate() {}
	static QString  removeComma(QString s);
	static QString  addComma(QString s);
	static long long otherToLong(QString s, int radix);
	vector<QString> longToOther(long long num) const;
};

