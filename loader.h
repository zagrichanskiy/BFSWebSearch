#ifndef PAGELOADER_H
#define PAGELOADER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Loader : public QObject
{
	Q_OBJECT

private:
	const int LOAD_LIMIT = 10000;
	QNetworkAccessManager *m_networkAccessManager;
public:
	explicit Loader(QObject *parent = 0);
	virtual ~Loader();
	QNetworkReply *load(QString url);
};

#endif // PAGELOADER_H
