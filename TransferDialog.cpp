#include "stdafx.h"
#include "TransferDialog.h"

TransferDialog::TransferDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_user = user;

	m_sqlOprtor = new SQLiteOperator(this);

	ui.lab_money->setText(QString::number(m_user->money) + tr(" RMB"));

	connect(ui.edit_tmoney, &QLineEdit::returnPressed, this, &TransferDialog::onBtnTransferClicked);
	connect(ui.btn_transfer, &QPushButton::clicked, this, &TransferDialog::onBtnTransferClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &TransferDialog::onBtnBackClicked);
}

TransferDialog::~TransferDialog()
{
}

void TransferDialog::onBtnTransferClicked()
{
	QString name = ui.edit_name->text();
	QString num = ui.edit_num->text();
	QString tmoney = ui.edit_tmoney->text();
	User* toUser = new User();

	if (!m_sqlOprtor->queryTable(num)) {
		//错误！未找到指定用户。检查帐号
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The specified user was not found."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Check"));
		msgBox->exec();
	}
	else
	{
		toUser = m_sqlOprtor->queryTable(num);
		if (toUser->id != name) {
			//错误！姓名与账号信息不符。检查信息
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("Name does not match account information."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Check"));
			msgBox->exec();
		}
		else
		{
			if (!isDigitString(tmoney)) {
				//错误！不规则输入。重输
				QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
					tr("Irregular Input."), QMessageBox::Ok, this);
				msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
				msgBox->exec();
			}
			else
			{
				if (tmoney.toDouble() > m_user->money)
				{
					//错误！余额不足，请确认金额。好的
					QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
						tr("The balance is insufficient, please confirm the amount."), QMessageBox::Ok, this);
					msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
					msgBox->exec();
				}
				else
				{
					if (toUser->num == m_user->num) {
						//提示！无需给自己转账。好的
						QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Prompt !"),
							tr("You don't have to transfer money to yourself."), QMessageBox::Ok, this);
						msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
						msgBox->exec();
					}
					else
					{
						//提示！收款方姓名：收款方帐号：转账金额： 元 确认转账吗？确认取消
						QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Tips !"),
							tr("To Name: ") + toUser->id 
							+ tr("\nTo Account: ") + toUser->num
							+ tr("\nTransfer Amount: ") + tmoney + tr(" RMB")
							+ tr("\nDo you confirm the transfer?"),
							QMessageBox::Ok | QMessageBox::Cancel, this);
						msgBox->button(QMessageBox::Ok)->setText(tr("Transfer"));
						msgBox->button(QMessageBox::Cancel)->setText(tr("Cancel"));
						if (msgBox->exec() == QMessageBox::Ok) {
							this->close();
							emit transferMoney(tmoney.toDouble(), toUser);
						}
					}
				}
			}
		}
	}
}

void TransferDialog::onBtnBackClicked()
{
	this->close();
}

//检测字符串是否为符合规则的数字
bool TransferDialog::isDigitString(const QString& src) {
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