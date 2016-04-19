#include "loader.h"
#include <QEventLoop>
#include <QTimer>

Loader::Loader(QObject *parent)
	: QObject(parent),
	  m_networkAccessManager(new QNetworkAccessManager())
{}

Loader::~Loader()
{
	delete m_networkAccessManager;
}

QNetworkReply *Loader::load(QString url)
{
	QEventLoop eventLoop;
	QNetworkRequest req(url);
	QTimer timer;
	timer.setSingleShot(true);

	connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
	connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
	timer.start(LOAD_LIMIT);

	req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
	QNetworkReply *reply = m_networkAccessManager->get(req);
	eventLoop.exec();

	return reply;
}
