#pragma once

#include <QDialog>

#include "ui_DepositDialog.h"
#include "SQLiteOperator.h"

class DepositDialog : public QDialog
{
	Q_OBJECT

public:
	DepositDialog(User* user, QWidget *parent = Q_NULLPTR);
	~DepositDialog();

signals:
	void despositMoney(double);

private slots:
	void onBtnDepositClicked();
	void onBtnBackClicked();

private:
	Ui::DepositDialog ui;

	User* m_user;

	bool isDigitString(const QString&);
};
