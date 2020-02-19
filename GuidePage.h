#pragma once

#include <QWidget>
#include <QDateTime>
#include <QTimer>

#include "ui_GuidePage.h"
#include "JoinPage.h"
#include "LoginPage.h"
#include "QtATM.h"
#include "global.h"
class GuidePage : public QWidget
{
	Q_OBJECT

public:
	GuidePage(QWidget* parent = Q_NULLPTR);
	~GuidePage();

private slots:
	void onBtnJionClicked();
	void onBtnLoginClicked();
	void onBtnCgLangueClicked();

private:
	Ui::GuidePage ui;

	int m_timerId;
	virtual void timerEvent(QTimerEvent*);

	void closeEvent(QCloseEvent*);
};
