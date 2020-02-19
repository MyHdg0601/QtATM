#include "stdafx.h"
#include "DepositDialog.h"

DepositDialog::DepositDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_user = user;

	ui.lab_money->setText(QString::number(m_user->money) + tr(" RMB"));

	connect(ui.edit_deposit, &QLineEdit::returnPressed, this, &DepositDialog::onBtnDepositClicked);
	connect(ui.btn_deposit, &QPushButton::clicked, this, &DepositDialog::onBtnDepositClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &DepositDialog::onBtnBackClicked);
}

DepositDialog::~DepositDialog()
{
}

void DepositDialog::onBtnDepositClicked()
{
	QString money = ui.edit_deposit->text();
	if (!isDigitString(money)) {
		//错误！不规则输入。重输
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Irregular Input."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else {
		this->close();
		emit despositMoney(money.toDouble());
	}
}

//检测字符串是否为符合规则的数字
bool DepositDialog::isDigitString(const QString& src) {
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

void DepositDialog::onBtnBackClicked()
{
	this->close();
}
