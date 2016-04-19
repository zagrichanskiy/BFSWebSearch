#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "page.h"
#include "queue.h"
#include "newurlslist.h"
#include "parser.h"
#include <atomic>

class Worker : public QThread
{
	Q_OBJECT

private:
	Queue<Page> *m_pPages;
	NewUrlsList *m_pNewUrls;
	std::atomic_bool done;
public:
	Worker(Queue<Page> *pPages, NewUrlsList *pNewUrls, QObject *parent = 0);

	void run();
	void setStatusFromRespond(Page *page, QString status, const Parser &parser) const;
	void addLinks(QString text, const QStringList &linkList);
	void stop();

signals:
	void pagesParsed();
};

#endif // WORKER_H
