#include "page.h"

const QVector<QString> Page::columnName { "#",
										  "Depth",
										  "URL",
										  "Load",
										  "Status" };

Page::Page(const QString &url, const QString &text, quint32 depth, QObject *pobj)
	: QObject(pobj),
	  m_url(url),
	  m_text(text),
	  m_depth(depth),
	  m_load(0),
	  m_status("Pending")
{}

quint32 Page::getIndex() const
{
	return m_index;
}

void Page::setIndex(quint32 index)
{
	m_index = index;
}

quint32 Page::getDepth() const
{
	return m_depth;
}

void Page::setDepth(const quint32 depth)
{
	m_depth = depth;
}

QString Page::getUrl() const
{
	return m_url;
}

void Page::setUrl(const QString &url)
{
	m_url = url;
	emit itemChanged(this);
}

QString Page::getText() const
{
	return m_text;
}

quint32 Page::getLoad() const
{
	return m_load;
}

void Page::setLoad(const quint32 load)
{
	m_load = load;
	emit itemChanged(this);
}

QString Page::getStatus() const
{
	return m_status;
}

void Page::setStatus(QString status)
{
	m_status = status;
	emit itemChanged(this);
}

void Page::setText(QString text)
{
	m_text = text;
}

quint32 Page::getColumns()
{
	return COLUMNS;
}

QString Page::getColumnName(ColumnN column)
{
	return columnName.at(column);
}
