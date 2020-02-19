#pragma once

#include <QDialog>

#include "ui_CashDialog.h"
#include "SQLiteOperator.h"

class CashDialog : public QDialog
{
	Q_OBJECT

public:
	CashDialog(User* user, QWidget* parent = Q_NULLPTR);
	~CashDialog();

signals:
	void cashMoney(double);

private slots:
	void onBtnCashClicked();
	void onBtnBackClicked();

private:
	Ui::CashDialog ui;

	User* m_user;

	bool isDigitString(const QString&);
};
