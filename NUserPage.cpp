#include "stdafx.h"
#include "NUserPage.h"

NUserPage::NUserPage(User* user, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_user = user;

	m_sqlOprtor = new SQLiteOperator(this);

	setTimeWord();

	connect(ui.btn_query, &QPushButton::clicked, this, &NUserPage::onBtnQueryClicked);
	connect(ui.btn_deposit, &QPushButton::clicked, this, &NUserPage::onBtnDepositClicked);
	connect(ui.btn_transfer, &QPushButton::clicked, this, &NUserPage::onBtnTransferClicked);
	connect(ui.btn_cash, &QPushButton::clicked, this, &NUserPage::onBtnCashClicked);
	connect(ui.btn_cacnt, &QPushButton::clicked, this, &NUserPage::onBtnCacntClicked);
	connect(ui.btn_cgpwd, &QPushButton::clicked, this, &NUserPage::onBtnCgpwdClicked);
	connect(ui.btn_logout, &QPushButton::clicked, this, &NUserPage::onBtnLogoutClicked);
}

NUserPage::~NUserPage()
{
}

//根据时间设置问候语
void NUserPage::setTimeWord()
{
	QTime time = QTime::currentTime();
	int hour = time.hour();
	QString words = "";
	if (hour >= 0 && hour < 5) {
		words = tr("Good evening");//晚上好
	}
	if (hour >= 5 && hour < 11) {
		words = tr("Good morning");//早上好
	}
	if (hour >= 11 && hour < 13) {
		words = tr("Good noon");//中午好
	}
	if (hour >= 13 && hour < 19) {
		words = tr("Good afternoon");//下午好
	}
	if (hour >= 19 && hour < 24) {
		words = tr("Good evening");//晚上好
	}
	words += tr(", ") + m_user->id;
	ui.lab_name->setText(words);
}

//查询信息
void NUserPage::onBtnQueryClicked()
{
	AccountDialog* accountDialog = new AccountDialog(m_user, this);
	accountDialog->exec();
}

//存款
void NUserPage::onBtnDepositClicked()
{
	DepositDialog* depositDialog = new DepositDialog(m_user, this);
	connect(depositDialog, &DepositDialog::despositMoney, this, &NUserPage::onDepositMoney);
	depositDialog->exec();
}

void NUserPage::onDepositMoney(double money)
{
	if (money >= 0)
	{
		m_user->money += money;
		m_sqlOprtor->updateData(m_user);
		//成功！存款金额： 元\n当前余额： 元 好的
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("Deposit: ") + QString::number(money) + tr(" RMB\nBalance: ")
			+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
}

//转账
void NUserPage::onBtnTransferClicked()
{
	TransferDialog* transferDialog = new TransferDialog(m_user, this);
	connect(transferDialog, &TransferDialog::transferMoney, this, &NUserPage::onTransferMoney);
	transferDialog->exec();
}

void NUserPage::onTransferMoney(double tmoney, User* toUser)
{
	m_user->money -= tmoney;
	m_sqlOprtor->updateData(m_user);
	toUser->money += tmoney;
	m_sqlOprtor->updateData(toUser);
	//成功！转账金额： 元\n当前余额： 元 好的
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("Transfer: ") + QString::number(tmoney) + tr(" RMB\nBalance: ")
		+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//取款
void NUserPage::onBtnCashClicked()
{
	CashDialog* cashDialog = new CashDialog(m_user, this);
	connect(cashDialog, &CashDialog::cashMoney, this, &NUserPage::onCashMoney);
	cashDialog->exec();
}

void NUserPage::onCashMoney(double money)
{
	if (money >= 0)
	{
		m_user->money -= money;
		m_sqlOprtor->updateData(m_user);
		//成功！取款金额： 元\n当前余额： 元 好的
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("Cash: ") + QString::number(money) + tr(" RMB\nBalance: ")
			+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
}

//销户
void NUserPage::onBtnCacntClicked()
{
	//注意！销毁帐户后无法恢复，请慎重考虑后联系高级管理员。好的
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Warning !"),
		tr("The account can not be restored after cancellation, please consider carefully and contact the senior manager."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//修改密码
void NUserPage::onBtnCgpwdClicked()
{
	ChangePwdDialog* changePwdDialog = new ChangePwdDialog(m_user, this);
	connect(changePwdDialog, &ChangePwdDialog::changePwd, this, &NUserPage::onChangePwd);
	changePwdDialog->exec();
}

void NUserPage::onChangePwd(QString npwd)
{
	m_user->pwd = npwd;
	m_sqlOprtor->updateData(m_user);
	//成功！密码修改成功，新密码为：记住了
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("The password was changed successfully. The new password is: ") + npwd, QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Remembered"));
	msgBox->exec();
}

//登出
void NUserPage::onBtnLogoutClicked()
{
	//提示！确认退出登录吗？确认取消
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Prompt !"),
		tr("Confirm logout?"), QMessageBox::Ok | QMessageBox::Cancel, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Logout"));
	msgBox->button(QMessageBox::Cancel)->setText(tr("Cancel"));
	if (msgBox->exec() == QMessageBox::Ok) {
		topPage = PAGE_GUIDE;

		this->close();

		guidePage->show();
	}
}

void NUserPage::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}