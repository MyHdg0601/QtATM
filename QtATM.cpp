#include "stdafx.h"
#include "QtATM.h"

QtATM::QtATM(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowFlag(Qt::WindowStaysOnTopHint);

	zhTranslator = new QTranslator(this);
	zhTranslator->load(":/QtATM/qtatm_zh.qm");

	connect(ui.btn_zh, &QPushButton::clicked, this, &QtATM::onBtnZhClicked);
	connect(ui.btn_en, &QPushButton::clicked, this, &QtATM::onBtnEnClicked);

	//m_settings = new QSettings("MyHdg", "QtATM");

	m_timerId = startTimer(500);

	if (!m_systemTrayIcon.isVisible()) {
		m_systemTrayIcon.setToolTip(tr("ATM Simulation System"));//ATM模拟系统
		m_systemTrayIcon.setIcon(QIcon(":/QtATM/QtATM.ico"));
		QMenu* menu = new QMenu();
		menu->addAction(ui.actionShow);
		menu->addSeparator();
		menu->addAction(ui.actionExit);
		m_systemTrayIcon.setContextMenu(menu);
		connect(&m_systemTrayIcon, &QSystemTrayIcon::activated, this, &QtATM::onSysyemTrayIconClicked);
		m_systemTrayIcon.show();
		connect(ui.actionShow, &QAction::triggered, this, &QtATM::onActionShow);
		connect(ui.actionExit, &QAction::triggered, this, &QtATM::onActionExit);
	}
}

void QtATM::onBtnZhClicked()
{
	topPage = PAGE_GUIDE;

	//m_settings->setValue("language", "zh");

	qApp->installTranslator(zhTranslator);

	guidePage = new GuidePage(this);
	guidePage->setWindowFlag(Qt::Window);
	guidePage->show();

	this->hide();
}

void QtATM::onBtnEnClicked()
{
	topPage = PAGE_GUIDE;

	//m_settings->setValue("language", "en");

	qApp->removeTranslator(zhTranslator);

	guidePage = new GuidePage(this);
	guidePage->setWindowFlag(Qt::Window);
	guidePage->show();

	this->hide();

	//QString language = m_settings->value("language").toString();
}

void QtATM::onActionShow()
{
	showTopPage();
}

void QtATM::onActionExit()
{
	m_systemTrayIcon.hide();
	QApplication::exit(0);
}

void QtATM::timerEvent(QTimerEvent* event) {
	if (event->timerId() == m_timerId)
	{
		QDateTime dateTime = QDateTime::currentDateTime();
		QString currentDateTime = dateTime.toString("yyyy-MM-dd hh:mm:ss");
		ui.lab_time->setText(currentDateTime);
	}
}

void QtATM::onSysyemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::DoubleClick) {
		showTopPage();
	}
}

//显示最顶层次页面
void QtATM::showTopPage()
{
	switch (topPage)
	{
	case PAGE_QTATM:
		qtATM->showNormal();
		break;
	case PAGE_GUIDE:
		guidePage->showNormal();
		break;
	case PAGE_JOIN:
		joinPage->showNormal();
		break;
	case PAGE_LOGIN:
		loginPage->showNormal();
		break;
	case PAGE_NUSER:
		nUserPage->showNormal();
		break;
	case PAGE_HUSER:
		hUserPage->showNormal();
		break;
	}
}

void QtATM::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}