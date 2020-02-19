#pragma once

#include <QDialog>

#include "ui_AccountDialog.h"
#include "SQLiteOperator.h"

class AccountDialog : public QDialog
{
	Q_OBJECT

public:
	AccountDialog(User* user, QWidget* parent = Q_NULLPTR);
	~AccountDialog();

private:
	Ui::AccountDialog ui;
};
