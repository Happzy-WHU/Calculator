#include "Thread_read.h"
Thread_read::Thread_read(QListWidget *lw_his)
{
	dm = new DataManager();
	this->lw_his = lw_his;
}
void Thread_read::run()
{
	lock.lockForRead();
	vec = dm->readFileJson();
	lock.unlock();
	for (int i = 0; vec.size() != i; i++)
	{
		if (i % 3 == 1 || i % 3 == 2)
		{
			auto temp_item = new QListWidgetItem(vec[i]);
			temp_item->setTextAlignment(Qt::AlignRight);
			if (i % 3 == 1)
			{
				lw_his->insertItem(0, temp_item);
			}
			lw_his->insertItem(1, temp_item);
		}
	}
	emit isDone();
}