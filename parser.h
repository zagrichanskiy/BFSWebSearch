#ifndef PARSER_H
#define PARSER_H

#include "loader.h"
#include <QStringList>
#include <QString>

class Parser
{
private:
	const QString m_pattern = "((https?|HTTPS?):\\/\\/)[^\\s]+([-a-zA-Z0-9@:%_\\+.~#?&//=])";
	Loader m_loader;
	QStringList m_links;
	bool m_found;
	quint32 m_load;
public:
	static const QString NO_ERRORS_STATUS;

	QString run(QString url, QString text);
	void findText(QString pageContent, QString text);
	void findLinks(QString pageContent);

	bool isFound() const;
	QStringList getLinks() const;
	quint32 getLoad() const;
};

#endif // PARSER_H
