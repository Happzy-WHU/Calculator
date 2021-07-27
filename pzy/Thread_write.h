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
	//重写run用来将写放入线程
	void run() override;
	DataManager *dm;
	string str;
	string ans;
	QReadWriteLock lock;
signals:
	void isDone();
};

