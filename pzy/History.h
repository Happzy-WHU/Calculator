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
	//������json�ļ��е���ʷ��¼��ʼ������ʷ��¼�б���
	void initToWidget() const;
	//���ڽ�str��ansд����ʷ��¼��ǰ�߱�ʾ���ʽ�����߱�ʾ���
	void addToWidget(QString str, QString ans);
	History();
};

