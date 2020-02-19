#pragma once

#include <QDialog>

#include "ui_ChangePwdDialog.h"
#include "SQLiteOperator.h"

class ChangePwdDialog : public QDialog
{
	Q_OBJECT

public:
	ChangePwdDialog(User* user, QWidget* parent = Q_NULLPTR);
	~ChangePwdDialog();

signals:
	void changePwd(QString);

private slots:
	void onCkbChecked(int);
	void onBtnChangeClicked();
	void onBtnBackClicked();

private:
	Ui::ChangePwdDialog ui;

	User* m_user;

	bool isDigitString(const QString&);
};