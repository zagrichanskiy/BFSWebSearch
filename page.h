#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QVector>

class Page : public QObject
{
	Q_OBJECT

public:
	enum ColumnN {
		INDEX,
		FIRST,
		DEPTH = FIRST,
		URL,
		LOAD,
		STATUS,
		LAST = STATUS,
		COLUMNS
	};
private:
	quint32 m_index;
	QString m_url;
	QString m_text;
	quint32 m_depth;
	quint32 m_load;
	QString m_status;
	static const QVector<QString> columnName;

public:
	explicit Page(const QString &url, const QString &text, quint32 depth = 0, QObject *pobj = 0);

	quint32 getIndex() const;
	void setIndex(quint32 index);
	quint32 getDepth() const;
	void setDepth(const quint32 depth);
	QString getUrl() const;
	void setUrl(const QString &url);
	QString getText() const;
	quint32 getLoad() const;
	void setLoad(const quint32 load);
	QString getStatus() const;
	void setStatus(QString status);
	void setText(QString text);
	static quint32 getColumns();
	static QString getColumnName(ColumnN column);

signals:
	void itemChanged(Page *);
};

#endif // PAGE_H
