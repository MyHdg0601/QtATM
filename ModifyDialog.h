#pragma once

#include <QDialog>

#include "ui_ModifyDialog.h"
#include "SQLiteOperator.h"

class ModifyDialog : public QDialog
{
	Q_OBJECT

public:
	ModifyDialog(int row, QString num, QWidget* parent = Q_NULLPTR);
	~ModifyDialog();

signals:
	void modifyInfo(int, User*, User*);

private slots:
	void onBtnModifyClicked();
	void onBtnBackClicked();

private:
	Ui::ModifyDialog ui;

	SQLiteOperator* m_sqlOprtor;
	int m_row;
	User* m_oUser;
	User* m_nUser;

	bool isDigitString(const QString&);
	bool checkNumRepeat(QString&);
};
