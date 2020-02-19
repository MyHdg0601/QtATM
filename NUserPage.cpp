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

//����ʱ�������ʺ���
void NUserPage::setTimeWord()
{
	QTime time = QTime::currentTime();
	int hour = time.hour();
	QString words = "";
	if (hour >= 0 && hour < 5) {
		words = tr("Good evening");//���Ϻ�
	}
	if (hour >= 5 && hour < 11) {
		words = tr("Good morning");//���Ϻ�
	}
	if (hour >= 11 && hour < 13) {
		words = tr("Good noon");//�����
	}
	if (hour >= 13 && hour < 19) {
		words = tr("Good afternoon");//�����
	}
	if (hour >= 19 && hour < 24) {
		words = tr("Good evening");//���Ϻ�
	}
	words += tr(", ") + m_user->id;
	ui.lab_name->setText(words);
}

//��ѯ��Ϣ
void NUserPage::onBtnQueryClicked()
{
	AccountDialog* accountDialog = new AccountDialog(m_user, this);
	accountDialog->exec();
}

//���
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
		//�ɹ������� Ԫ\n��ǰ�� Ԫ �õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("Deposit: ") + QString::number(money) + tr(" RMB\nBalance: ")
			+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
}

//ת��
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
	//�ɹ���ת�˽� Ԫ\n��ǰ�� Ԫ �õ�
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("Transfer: ") + QString::number(tmoney) + tr(" RMB\nBalance: ")
		+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//ȡ��
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
		//�ɹ���ȡ��� Ԫ\n��ǰ�� Ԫ �õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("Cash: ") + QString::number(money) + tr(" RMB\nBalance: ")
			+ QString::number(m_user->money) + tr(" RMB"), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
}

//����
void NUserPage::onBtnCacntClicked()
{
	//ע�⣡�����ʻ����޷��ָ��������ؿ��Ǻ���ϵ�߼�����Ա���õ�
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Warning !"),
		tr("The account can not be restored after cancellation, please consider carefully and contact the senior manager."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//�޸�����
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
	//�ɹ��������޸ĳɹ���������Ϊ����ס��
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("The password was changed successfully. The new password is: ") + npwd, QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Remembered"));
	msgBox->exec();
}

//�ǳ�
void NUserPage::onBtnLogoutClicked()
{
	//��ʾ��ȷ���˳���¼��ȷ��ȡ��
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