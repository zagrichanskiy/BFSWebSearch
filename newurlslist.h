#ifndef NEWPAGESLIST_H
#define NEWPAGESLIST_H

#include <list>
#include <QMutex>
#include <QString>

class NewUrlsList : public std::list<QString>
{
private:
	mutable QMutex mutex;
public:
	void push_back(QString item);
	bool empty() const;
	quint32 size() const;
	void clear();
};

#endif // NEWPAGESLIST_H
