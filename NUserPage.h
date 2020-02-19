#pragma once

#include <QWidget>

#include "ui_NUserPage.h"
#include "SQLiteOperator.h"
#include "GuidePage.h"
#include "AccountDialog.h"
#include "DepositDialog.h"
#include "CashDialog.h"
#include "ChangePwdDialog.h"
#include "TransferDialog.h"
#include "global.h"

class NUserPage : public QWidget
{
	Q_OBJECT

public:
	NUserPage(User* user, QWidget* parent = Q_NULLPTR);
	~NUserPage();

private slots:
	void onBtnQueryClicked();
	void onBtnDepositClicked();
	void onBtnTransferClicked();
	void onBtnCashClicked();
	void onBtnCacntClicked();
	void onBtnCgpwdClicked();
	void onBtnLogoutClicked();
	void onDepositMoney(double);
	void onCashMoney(double);
	void onChangePwd(QString);
	void onTransferMoney(double, User*);

private:
	Ui::NUserPage ui;

	User* m_user;

	SQLiteOperator* m_sqlOprtor;

	void setTimeWord();

	void closeEvent(QCloseEvent*);
};
