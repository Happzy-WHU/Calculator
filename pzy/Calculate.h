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
	//��ѧ��������������¼�
	//str������Ǳ��ʽ����ַ�����ans������ǽ������ַ�����btn_text�����û�����İ�ť���ı�
	//c����ť���������ͣ�������һ�����ֻ��������
	//frame_his���������ʷ��¼�Ķ��������޸���ʷ��¼����ʾ
	//����ֵ�Ǽ���Ľ����vec[0]��ʾ�Ǳ��ʽ����ı���vec[1]��ʾ���ǽ������ı�
	vector<QString> calcEvent(QString str, QString ans, QString btn_text,
		 History *frame_his) ;
	//����ת����������������¼�
	//str���������ʾ��ĳ�����Ƶ��ַ�����btn_text�����û�����İ�ť���ı���currentIndex����str�Ǽ����Ƶ���
	//c����ť���������ͣ�������һ�����ֻ��������
	//����ֵvec 0-3��ʾ16��10��8��2���Ƶ�Ӧ����ʾ�Ľ��
	vector<QString> calcConvertEvent(QString str, QString btn_text,
		char currentIndex, char c) const;
	stack<double> num;
	stack<char> op;
	void calcOnce();
	bool judgePrior(char c);
	//��Ϊstring����ֱ��ͨ���±������ʣ���QString��Ҫʹ��mid�����ʣ����ѡ��
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

