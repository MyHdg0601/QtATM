#pragma once

#include <QWidget>

#include "ui_TransferDialog.h"
#include "SQLiteOperator.h"

class TransferDialog : public QDialog
{
	Q_OBJECT

public:
	TransferDialog(User* user, QWidget* parent = Q_NULLPTR);
	~TransferDialog();

signals:
	void transferMoney(double, User*);

private slots:
	void onBtnTransferClicked();
	void onBtnBackClicked();

private:
	Ui::TransferDialog ui;

	User* m_user;

	SQLiteOperator* m_sqlOprtor;

	bool isDigitString(const QString&);
};
