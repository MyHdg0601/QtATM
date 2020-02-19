#pragma once

#include <QWidget>

#include "ui_LoginPage.h"
#include "GuidePage.h"
#include "SQLiteOperator.h"
#include "NUserPage.h"
#include "HUserPage.h"
#include "global.h"

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget* parent = Q_NULLPTR);
	~LoginPage();

private slots:
	void onCkbChecked(int);
	void onBtnFPwdClicked();
	void onBtnLoginClicked();
	void onBtnBackClicked();

private:
	Ui::LoginPage ui;

	User* m_user;

	SQLiteOperator* m_sqlOprtor;

	short m_countError;//错误次数
	int m_banTime;//禁止登录时间
	int m_countBan;//禁止登录次数
	const short m_initBanTime = 5;//初始禁止时间

	bool checkInformation(QString, QString);

	int m_timerId;
	virtual void timerEvent(QTimerEvent*);

	void closeEvent(QCloseEvent*);
};
