#include "tablemodel.h"

TableModel::TableModel(QObject *pobj)
	: QAbstractTableModel(pobj),
	  m_nColumns(Page::getColumns()),
	  m_nRows(0)
{}

int TableModel::rowCount(const QModelIndex &parent) const
{
	(void) parent;

	return m_nRows;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
	(void) parent;

	return m_nColumns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole) {
		return QVariant();
	}

	const Page *item = m_list.at(index.row());
	switch (index.column()) {
	case Page::INDEX:
		return item->getIndex();
	case Page::DEPTH:
		return item->getDepth();
	case Page::URL:
		return item->getUrl();
	case Page::LOAD:
		return item->getLoad();
	case Page::STATUS:
		return item->getStatus();
	default:
		return QVariant();
	}
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
		return QVariant();
	}

	return Page::getColumnName(static_cast<Page::ColumnN>(section));
}

void TableModel::clear()
{
	for (Page *page : m_list) {
		delete page;
	}
	m_nRows = 0;
	m_list.clear();
	m_hash.clear();
}

void TableModel::addItem(Page *item)
{
	quint32 row = m_nRows++;
	item->setParent(this);
	m_hash[item] = row;
	item->setIndex(row + 1);
	m_list.push_back(item);
	connect(item, SIGNAL(itemChanged(Page*)), this, SLOT(itemChanged(Page*)));
}

void TableModel::itemChanged(Page *item)
{
	quint32 row = m_hash[item];
	emit dataChanged(createIndex(row, 0), createIndex(row, Page::COLUMNS));
}

void TableModel::newPages(QList<Page *> list)
{
	for (Page *item : list) {
		addItem(item);
	}
	emit layoutChanged();
}
