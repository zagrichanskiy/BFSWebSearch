#include "newurlslist.h"
#include <QMutexLocker>

void NewUrlsList::push_back(QString item)
{
	QMutexLocker lk(&mutex);
	std::list<QString>::push_back(item);
}

bool NewUrlsList::empty() const
{
	QMutexLocker lk(&mutex);
	return std::list<QString>::empty();
}

quint32 NewUrlsList::size() const
{
	QMutexLocker lk(&mutex);
	return std::list<QString>::size();
}

void NewUrlsList::clear()
{
	QMutexLocker lk(&mutex);
	std::list<QString>::clear();
}
