#include "stdafx.h"
#include "UserItemDrawer.h"

UserItemDrawer::UserItemDrawer(QObject* parent)
	: QStyledItemDelegate(parent)
{
}

UserItemDrawer::~UserItemDrawer()
{
}

QSize UserItemDrawer::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QSize size = QStyledItemDelegate::sizeHint(option, index);
	size.setHeight(30);
	return size;
}

void UserItemDrawer::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QRect rect = option.rect;//获得目标矩形
	rect.adjust(2, 2, -2, -2);//缩小一圈，留出空白间隔

	//取得数据
	QString name = index.data(Qt::UserRole).toString();
	QString num = index.data(Qt::UserRole + 1).toString();
	QString money = index.data(Qt::UserRole + 2).toString();

	//绘制被选中状态
	if (option.state & QStyle::State_Selected) {
		painter->setBrush(Qt::GlobalColor::lightGray);
		painter->drawRect(rect);
		painter->setBrush(Qt::NoBrush);
	}

	//显示姓名
	QRect nameRect = rect;
	nameRect.setLeft(rect.left() + 10);
	nameRect.setRight(rect.left() + 220);
	painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, name);

	//显示帐号
	QRect numRect = rect;
	numRect.setLeft(rect.left() + 222);
	numRect.setRight(rect.left() + 350);
	painter->drawText(numRect, Qt::AlignLeft | Qt::AlignVCenter, num);

	//显示余额
	QRect moneyRect = rect;
	moneyRect.setLeft(rect.left() + 400);
	moneyRect.setRight(rect.left() + 530);
	painter->drawText(moneyRect, Qt::AlignRight | Qt::AlignVCenter, money);
}