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
	QRect rect = option.rect;//���Ŀ�����
	rect.adjust(2, 2, -2, -2);//��СһȦ�������հ׼��

	//ȡ������
	QString name = index.data(Qt::UserRole).toString();
	QString num = index.data(Qt::UserRole + 1).toString();
	QString money = index.data(Qt::UserRole + 2).toString();

	//���Ʊ�ѡ��״̬
	if (option.state & QStyle::State_Selected) {
		painter->setBrush(Qt::GlobalColor::lightGray);
		painter->drawRect(rect);
		painter->setBrush(Qt::NoBrush);
	}

	//��ʾ����
	QRect nameRect = rect;
	nameRect.setLeft(rect.left() + 10);
	nameRect.setRight(rect.left() + 220);
	painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, name);

	//��ʾ�ʺ�
	QRect numRect = rect;
	numRect.setLeft(rect.left() + 222);
	numRect.setRight(rect.left() + 350);
	painter->drawText(numRect, Qt::AlignLeft | Qt::AlignVCenter, num);

	//��ʾ���
	QRect moneyRect = rect;
	moneyRect.setLeft(rect.left() + 400);
	moneyRect.setRight(rect.left() + 530);
	painter->drawText(moneyRect, Qt::AlignRight | Qt::AlignVCenter, money);
}