#include "stdafx.h"
#include "GuidePage.h"

GuidePage::GuidePage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btn_join, &QPushButton::clicked, this, &GuidePage::onBtnJionClicked);
	connect(ui.btn_login, &QPushButton::clicked, this, &GuidePage::onBtnLoginClicked);
	connect(ui.btn_cglang, &QPushButton::clicked, this, &GuidePage::onBtnCgLangueClicked);

	m_timerId = startTimer(500);
}

GuidePage::~GuidePage()
{
}

void GuidePage::onBtnJionClicked()
{
	topPage = PAGE_JOIN;

	joinPage = new JoinPage(this);
	joinPage->setWindowFlag(Qt::Window);
	joinPage->show();

	this->hide();
}

void GuidePage::onBtnLoginClicked()
{
	topPage = PAGE_LOGIN;

	loginPage = new LoginPage(this);
	loginPage->setWindowFlag(Qt::Window);
	loginPage->show();

	this->hide();
}

void GuidePage::onBtnCgLangueClicked()
{
	topPage = PAGE_QTATM;

	this->close();

	qtATM->show();
}

void GuidePage::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_timerId)
	{
		QDateTime dateTime = QDateTime::currentDateTime();
		QString currentDateTime = dateTime.toString("yyyy-MM-dd hh:mm:ss");
		ui.lab_time->setText(currentDateTime);
	}
}

void GuidePage::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}