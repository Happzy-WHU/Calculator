#pragma once
//#include"json.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include<QJsonParseError>
#include<QJsonDocument>
#include<fstream>
#include<QFile>
#include<qdebug.h>
using std::string;
using std::vector;
using std::ios;

class DataManager
{
public:
	//���ַ���д�뱾��json�ļ�
	//str��ʾ���ʽ��ans���������
	static void writeFileJson(string str, string ans);
	//��json�ж�ȡ��ʷ��¼���������ٻָ���ʷ��¼��ʾ
	vector<QString> readFileJson() const;
};

