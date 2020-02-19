#include "stdafx.h"
#include "SearchDialog.h"

SearchDialog::SearchDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.edit_num, &QLineEdit::returnPressed, this, &SearchDialog::onBtnSearchClicked);
	connect(ui.btn_search, &QPushButton::clicked, this, &SearchDialog::onBtnSearchClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &SearchDialog::onBtnBackClicked);
}

SearchDialog::~SearchDialog()
{
}

void SearchDialog::onBtnSearchClicked()
{
	QString num = ui.edit_num->text();
	if (!isDigitString(num) || num.length() != 10)
	{
		//错误！账号应该为10位纯数字。重输
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The account number should be 10 digits."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else
	{
		this->close();
		emit searchUser(num);
	}
}

void SearchDialog::onBtnBackClicked()
{
	this->close();
}

//检测字符串是否为纯数字
bool SearchDialog::isDigitString(const QString& src) {
	int length = src.length();
	if (length <= 0) {
		return false;
	}

	int i = 0;
	for (; i < length; i++) {
		if (src.at(i) < '0' || src.at(i) > '9') {
			break;
		}
	}

	return i >= length;
}