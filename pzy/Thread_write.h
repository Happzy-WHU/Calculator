#pragma once
#include <QThread>
#include"DataManager.h"
#include <QReadWriteLock>

class Thread_write :
	public QThread
{
	Q_OBJECT
public:
	Thread_write();
	//��дrun������д�����߳�
	void run() override;
	DataManager *dm;
	string str;
	string ans;
	QReadWriteLock lock;
signals:
	void isDone();
};

