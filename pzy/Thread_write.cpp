#include "Thread_write.h"
Thread_write::Thread_write()
{
	dm = new DataManager();
}
void Thread_write::run()
{
	lock.lockForWrite();
	dm->writeFileJson(str, ans);
	lock.unlock();
	emit isDone();
}