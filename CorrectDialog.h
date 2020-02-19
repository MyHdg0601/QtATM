#pragma once

#include <QDialog>

#include "SQLiteOperator.h"
#include "ui_CorrectDialog.h"

class CorrectDialog : public QDialog
{
	Q_OBJECT

public:
	CorrectDialog(int row, User* user, QWidget *parent = Q_NULLPTR);
	~CorrectDialog();

signals:
	void correctBalance(int, User*);

private slots:
	void onBtnCorrectClicked();
	void onBtnBackClicked();

private:
	Ui::CorrectDialog ui;

	int m_row;
	User* m_user;

	bool isDigitString(const QString&);
};
