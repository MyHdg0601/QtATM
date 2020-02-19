#pragma once

#include <QStyledItemDelegate>
#include <QPainter>

class UserItemDrawer : public QStyledItemDelegate
{
	Q_OBJECT

public:
	UserItemDrawer(QObject* parent);
	~UserItemDrawer();

private:
	virtual QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const;
	virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
};
