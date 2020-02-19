#include "stdafx.h"
#include "CashDialog.h"

CashDialog::CashDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_user = user;

	ui.lab_money->setText(QString::number(m_user->money) + tr(" RMB"));

	connect(ui.edit_cash, &QLineEdit::returnPressed, this, &CashDialog::onBtnCashClicked);
	connect(ui.btn_cash, &QPushButton::clicked, this, &CashDialog::onBtnCashClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &CashDialog::onBtnBackClicked);
}

CashDialog::~CashDialog()
{
}

void CashDialog::onBtnCashClicked()
{
	QString money = ui.edit_cash->text();
	if (!isDigitString(money)) {
		//错误！不规则输入。重输
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Irregular Input."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else
	{
		if (money.toDouble() > m_user->money)
		{
			//错误！余额不足，请确认金额。好的
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("Balance is not enough, please confirm the money."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
			msgBox->exec();
		}
		else {
			this->close();
			emit cashMoney(money.toDouble());
		}
	}
}

//检测字符串是否为符合规则的数字
bool CashDialog::isDigitString(const QString& src) {
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

void CashDialog::onBtnBackClicked()
{
	this->close();
}