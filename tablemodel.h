#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include <QHash>
#include <QList>
#include "page.h"

class TableModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	QVector<Page *> m_list;
	QHash<Page *, quint32> m_hash;
	quint32 m_nColumns;
	quint32 m_nRows;

public:
	TableModel(QObject *pobj = 0);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void clear();

public slots:
	void newPages(QList<Page *> list);
	void itemChanged(Page *);

private:
	void addItem(Page *item);
};

#endif // TABLEMODEL_H
