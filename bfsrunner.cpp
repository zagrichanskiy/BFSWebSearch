#include "bfsrunner.h"

BFSRunner::BFSRunner(QObject *parent)
	: QObject(parent)
{}

void BFSRunner::runBfs(QString url, QString text, quint32 threads, quint32 urls)
{
	m_maxThreads = threads;
	m_urlsLeft = urls - 1;
	m_depth = 0;
	m_text = text;
	m_visited.insert(url);
	Page *page = new Page(url, text);
	m_pages.push(page);
	emit newPages(QList<Page *>() << page);

	run();
}

void BFSRunner::run()
{
	quint32 count = 0;
	Worker *worker;
	for (; count < m_maxThreads; ++count) {
		worker = new Worker(&m_pages, &m_newUrls);
		connect(worker, SIGNAL(pagesParsed()), this, SLOT(pagesParsed()));
		worker->start();
		m_threads << worker;
	}
}

void BFSRunner::stop()
{
	for (Worker *thread : m_threads) {
		if (thread->isRunning()) {
			thread->stop();
			thread->wait();
		}
	}
	m_pages.clear();
	m_newUrls.clear();
	m_threads.clear();
	m_visited.clear();
}

void BFSRunner::pagesParsed()
{
	if (m_urlsLeft == 0) {
		stop();
		emit bfsDone();
	}
	else {
		m_depth++;
		QList<Page *> pages;
		Page *page;
		for (const QString &url : m_newUrls) {
			if (m_visited.count(url) > 0) {
				continue;
			}
			m_visited.insert(url);
			m_urlsLeft--;
			page = new Page(url, m_text, m_depth);
			m_pages.push(page);
			pages << page;
			if (m_urlsLeft == 0) {
				break;
			}
		}
		m_newUrls.clear();
		emit newPages(pages);
	}
}
