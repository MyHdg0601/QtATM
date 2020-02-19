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

	short m_countError;//�������
	int m_banTime;//��ֹ��¼ʱ��
	int m_countBan;//��ֹ��¼����
	const short m_initBanTime = 5;//��ʼ��ֹʱ��

	bool checkInformation(QString, QString);

	int m_timerId;
	virtual void timerEvent(QTimerEvent*);

	void closeEvent(QCloseEvent*);
};
