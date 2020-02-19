#include"stdafx.h"
#include "RestPwdDialog.h"

RestPwdDialog::RestPwdDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_user = user;

	connect(ui.ckb_spwd, &QCheckBox::stateChanged, this, &RestPwdDialog::onCkbChecked);
	connect(ui.edit_mpwd, &QLineEdit::returnPressed, this, &RestPwdDialog::onBtnRestClicked);
	connect(ui.btn_rest, &QPushButton::clicked, this, &RestPwdDialog::onBtnRestClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &RestPwdDialog::onBtnBackClicked);
}

RestPwdDialog::~RestPwdDialog()
{
}

void RestPwdDialog::onCkbChecked(int state)
{
	if (state == Qt::Unchecked) {
		ui.edit_rest->setEchoMode(QLineEdit::Password);
		ui.edit_mpwd->setEchoMode(QLineEdit::Password);
	}
	else {
		ui.edit_rest->setEchoMode(QLineEdit::Normal);
		ui.edit_mpwd->setEchoMode(QLineEdit::Normal);
	}
}

void RestPwdDialog::onBtnRestClicked()
{
	QString pwd = ui.edit_rest->text();
	QString mpwd = ui.edit_mpwd->text();

	if (!isDigitString(pwd) || pwd.length() != 6)
	{
		//错误！新密码必须为6位纯数字密码。重输
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The new password must be a 6-bit pure digital password."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else
	{
		if (mpwd != "0601") {
			//错误！管理密码校验不通过。重输
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("The MnagPwd check failed."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
			msgBox->exec();
		}
		else
		{
			m_user->pwd = pwd;
			this->close();
			emit restPassword(m_user);
		}
	}
}

void RestPwdDialog::onBtnBackClicked()
{
	this->close();
}

//检测字符串是否为纯数字
bool RestPwdDialog::isDigitString(const QString& src) {
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