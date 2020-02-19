#include "stdafx.h"
#include "CorrectDialog.h"

CorrectDialog::CorrectDialog(int row, User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_row = row;
	m_user = user;

	ui.lab_money->setText(QString::number(m_user->money) + tr(" RMB"));
	ui.edit_correct->setText(QString::number(m_user->money));

	connect(ui.edit_correct, &QLineEdit::returnPressed, this, &CorrectDialog::onBtnCorrectClicked);
	connect(ui.btn_correct, &QPushButton::clicked, this, &CorrectDialog::onBtnCorrectClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &CorrectDialog::onBtnBackClicked);
}

CorrectDialog::~CorrectDialog()
{
}

void CorrectDialog::onBtnCorrectClicked()
{
	QString money = ui.edit_correct->text();
	QString mpwd = ui.edit_mpwd->text();

	if (!isDigitString(money)) {
		//错误！不规则输入。重输
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Irregular Input."), QMessageBox::Ok, this);
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
			m_user->money = money.toDouble();
			this->close();
			emit correctBalance(m_row, m_user);
		}
	}
}

void CorrectDialog::onBtnBackClicked()
{
	this->close();
}

//检测字符串是否为符合规则的数字
bool CorrectDialog::isDigitString(const QString& src) {
	int length = src.length();
	if (length <= 0) {
		return false;
	}

	int i = 0;
	for (; i < length; i++) {
		if (src.at(i) < '0' || src.at(i) > '9') {
			if (src.at(i) != '.') break;
		}
	}

	return i >= length;
}