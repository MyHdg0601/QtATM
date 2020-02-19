#pragma once

#include <QWidget>

#include "ui_HUserPage.h"
#include "SQLiteOperator.h"
#include "GuidePage.h"
#include "global.h"
#include "UserItemDrawer.h"
#include "ModifyDialog.h"
#include "CorrectDialog.h"
#include "RestPwdDialog.h"
#include "SearchDialog.h"

class HUserPage : public QWidget
{
	Q_OBJECT

public:
	HUserPage(User* user, QWidget* parent = Q_NULLPTR);
	~HUserPage();

private slots:
	void onBtnModifyClicked();
	void onBtnCorrectClicked();
	void onBtnRestPwdClicked();
	void onBtnDestoryClicked();
	void onBtnSearchClicked();
	void onBtnCUsClicked();
	void onBtnLogoutClicked();
	void onModifyInfo(int, User*, User*);
	void onCorrectBalance(int, User*);
	void onRestPassword(User*);
	void onSearchUser(QString);

private:
	Ui::HUserPage ui;

	User* m_user;
	QList<User*> m_allData;

	SQLiteOperator* m_sqlOprtor;

	void addItem(QString, QString, QString);
	void setTimeWord();

	void setListData();

	void closeEvent(QCloseEvent*);
};
