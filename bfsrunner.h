#ifndef BFSRUNNER_H
#define BFSRUNNER_H

#include <QObject>
#include "page.h"
#include <QList>
#include "queue.h"
#include "worker.h"
#include "newurlslist.h"
#include <set>

class BFSRunner : public QObject
{
	Q_OBJECT

private:
	quint32 m_maxThreads;
	quint32 m_urlsLeft;
	Queue<Page> m_pages;
	NewUrlsList m_newUrls;
	QList<Worker *> m_threads;
	quint32 m_depth;
	QString m_text;
	std::set<QString> m_visited;

public:
	explicit BFSRunner(QObject *parent = 0);
	void runBfs(QString url, QString text, quint32 threads, quint32 urls);
	void run();
	void stop();

signals:
	void newPages(QList<Page *> list);
	void bfsDone();

public slots:
	void pagesParsed();
};

#endif // BFSRUNNER_H
