#include "parser.h"
#include <QRegExp>

const QString Parser::NO_ERRORS_STATUS = "Success";

void Parser::findText(QString pageContent, QString text)
{
	m_found = pageContent.contains(text);
}

void Parser::findLinks(QString pageContent)
{
	QRegExp regExp(m_pattern);
	int pos = 0;

	m_links.clear();
	while ((pos = regExp.indexIn(pageContent, pos)) != -1) {
		m_links << regExp.cap(0);
		pos += regExp.matchedLength();
	}
}

QString Parser::run(QString url, QString text)
{
	QString status;

	QNetworkReply *reply = m_loader.load(url);
	if (reply->error() == QNetworkReply::NoError) {
		status = NO_ERRORS_STATUS;
		QByteArray byteArray = reply->readAll();
		m_load = byteArray.size();
		QString pageContent = QString(byteArray.data());
		findText(pageContent, text);
		findLinks(pageContent);
	}
	else {
		status = "Failure: " + reply->errorString();
		m_links.clear();
		m_found = false;
	}

	delete reply;
	return status;
}

bool Parser::isFound() const
{
	return m_found;
}

QStringList Parser::getLinks() const
{
	return m_links;
}

quint32 Parser::getLoad() const
{
	return m_load;
}
