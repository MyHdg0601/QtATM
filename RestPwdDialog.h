#pragma once

#include <QDialog>

#include "ui_RestPwdDialog.h"
#include "SQLiteOperator.h"

class RestPwdDialog : public QDialog
{
	Q_OBJECT

public:
	RestPwdDialog(User* user, QWidget *parent = Q_NULLPTR);
	~RestPwdDialog();

signals:
	void restPassword(User*);

private slots:
	void onCkbChecked(int);
	void onBtnRestClicked();
	void onBtnBackClicked();

private:
	Ui::RestPwdDialog ui;

	User* m_user;

	bool isDigitString(const QString&);
};
