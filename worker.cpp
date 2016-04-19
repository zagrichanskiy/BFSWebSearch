#include "worker.h"

Worker::Worker(Queue<Page> *pPages, NewUrlsList *pNewUrls, QObject *parent)
	: QThread(parent),
	  m_pPages(pPages),
	  m_pNewUrls(pNewUrls)
{
	connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
	done = false;
}

void Worker::run()
{
	Page *page;
	Parser parser;

	while (!done) {
		page = m_pPages->wait_and_pop();
		if (page) {
			page->setStatus("Parsing...");
			QString status = parser.run(page->getUrl(), page->getText());
			setStatusFromRespond(page, status, parser);
			if (status == Parser::NO_ERRORS_STATUS) {
				page->setLoad(parser.getLoad());
				addLinks(page->getText(), parser.getLinks());
			}

			if (m_pPages->empty()) {
				emit pagesParsed();
			}
		}
	}
}

void Worker::setStatusFromRespond(Page *page, QString status, const Parser &parser) const
{
	if (status == Parser::NO_ERRORS_STATUS) {
		QString resultStatus;
		resultStatus = "Text '" + page->getText() + "' "
				+ (parser.isFound() ? "is found" : "isn't found");
		page->setStatus(resultStatus);
	}
	else {
		page->setStatus(status);
	}
}

void Worker::addLinks(QString text, const QStringList &linkList)
{
	for (const QString &newUrl : linkList) {
		m_pNewUrls->push_back(newUrl);
	}
}

void Worker::stop()
{
	done = true;
	m_pPages->release();
}
