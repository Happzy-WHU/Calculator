#pragma once
#include <QThread>
#include"DataManager.h"
#include "QListWidget"
#include <QReadWriteLock>

class Thread_read :
	public QThread
{
	Q_OBJECT
public:
	Thread_read(QListWidget *lw_his);
	//重写run，用来将读操作放入线程
	void run() override;
	DataManager *dm;
	vector<QString> vec;
	QListWidget *lw_his;
	QReadWriteLock lock;
signals:
	void isDone();
};

