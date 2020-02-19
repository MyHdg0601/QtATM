#include "stdafx.h"
#include "AccountDialog.h"

AccountDialog::AccountDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lab_id->setText(user->id);
	ui.lab_num->setText(user->num);
	ui.lab_money->setText(QString::number(user->money) + tr(" RMB"));
}

AccountDialog::~AccountDialog()
{
}