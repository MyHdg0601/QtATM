#include "stdafx.h"
#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_user = new User();
	m_sqlOprtor = new SQLiteOperator(this);
	m_countError = 3;
	m_banTime = m_initBanTime;
	m_countBan = 0;

	connect(ui.edit_pwd, &QLineEdit::returnPressed, this, &LoginPage::onBtnLoginClicked);
	connect(ui.ckb_spwd, &QCheckBox::stateChanged, this, &LoginPage::onCkbChecked);
	connect(ui.btn_fpwd, &QPushButton::clicked, this, &LoginPage::onBtnFPwdClicked);
	connect(ui.btn_login, &QPushButton::clicked, this, &LoginPage::onBtnLoginClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &LoginPage::onBtnBackClicked);
}

LoginPage::~LoginPage()
{
}

void LoginPage::onCkbChecked(int state)
{
	if (state == Qt::Unchecked) {
		ui.edit_pwd->setEchoMode(QLineEdit::Password);
	}
	else {
		ui.edit_pwd->setEchoMode(QLineEdit::Normal);
	}
}

void LoginPage::onBtnFPwdClicked()
{
	//提示！忘记密码，请联系高级管理员重置。好的
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Prompt !"),
		tr("if you forget your password, please contact Senior Manager to reset it."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

void LoginPage::onBtnLoginClicked()
{
	QString num = ui.edit_num->text();
	QString pwd = ui.edit_pwd->text();

	if (!checkInformation(num, pwd)) {
		m_countError--;
		//错误！身份校验不通过，请检查账号及密码！\n若身份校验失败3次，将锁定登录功能！\n(当前剩余错误次数：核对后再试
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Identity check failed, please check the account and password !\nIf the authentication fails three times, the login function will be locked !\n( Current number of remaining errors: ")
			+ QString::number(m_countError) + tr(" )"), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Check"));
		msgBox->exec();
		if (m_countError == 0) {
			ui.btn_login->setEnabled(false);
			ui.btn_back->setText(tr("EXIT SYSTEM"));//退出系统
			m_countBan++;
			m_timerId = startTimer(1000);
		}
	}
	else {
		//成功！身份校验通过，登陆成功。好的
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("Identity check is passed and landing is successful."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
		if (m_user->isHighU) {
			topPage = PAGE_HUSER;

			this->close();

			hUserPage = new HUserPage(m_user, this);
			hUserPage->setWindowFlag(Qt::Window);
			hUserPage->show();
		}
		else {
			topPage = PAGE_NUSER;

			this->close();

			nUserPage = new NUserPage(m_user, this);
			nUserPage->setWindowFlag(Qt::Window);
			nUserPage->show();
		}
	}
}

bool LoginPage::checkInformation(QString num, QString pwd)
{
	m_user = m_sqlOprtor->queryTable(num);

	if (m_user == NULL) {
		return false;
	}
	if (num != m_user->num || pwd != m_user->pwd) {
		return false;
	}
	return true;
}

void LoginPage::onBtnBackClicked()
{
	if (ui.btn_back->text() == tr("EXIT SYSTEM")) {//退出系统
		qtATM->m_systemTrayIcon.hide();
		QApplication::exit(0);
	}
	else
	{
		topPage = PAGE_GUIDE;

		this->close();

		guidePage->show();
	}
}

void LoginPage::timerEvent(QTimerEvent* event) {
	if (event->timerId() == m_timerId) {
		if (m_banTime > 0) {
			ui.btn_login->setText(tr("( ") + QString::number(m_banTime) + tr("s REMOVE LOGIN BAN)"));//秒后解除登录禁止
			m_banTime--;
		}
		else
		{
			ui.btn_login->setEnabled(true);
			ui.btn_login->setText(tr("LOGIN"));//登录
			ui.btn_back->setText(tr("CANCEL"));//返回

			m_countError = 1;//禁止时间结束后增加一次错误机会
			m_banTime = qPow(m_initBanTime, m_countBan + 1);//禁止时间成指数增长

			killTimer(m_timerId);
		}
	}
}

void LoginPage::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}