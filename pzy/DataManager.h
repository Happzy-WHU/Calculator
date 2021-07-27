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
	//将字符串写入本地json文件
	//str表示表达式，ans代表计算结果
	static void writeFileJson(string str, string ans);
	//从json中读取历史记录，用来快速恢复历史记录显示
	vector<QString> readFileJson() const;
};

