#pragma once
#include<QListWidget>
#include<QLabel>
#include<QBoxLayout>
#include"DataManager.h"
#include "Thread_read.h"
class History :
	public QFrame
{
private:
	QLabel *title;
	QVBoxLayout *layout_his;
	QString temp_str;
	QString temp_ans;
	DataManager *dm;
	QLabel *temp_label;
	QListWidgetItem *temp_item;
	QVBoxLayout *temp_layout;

public:
	QListWidget *listWgt_his;
	//用来将json文件中的历史记录初始化到历史记录列表中
	void initToWidget() const;
	//用于将str和ans写入历史记录，前者表示表达式，后者表示结果
	void addToWidget(QString str, QString ans);
	History();
};

