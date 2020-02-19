#pragma once

#include <QtWidgets/QMainWindow>
//#include <QSettings>
#include <QDateTime>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QTranslator>

#include "ui_QtATM.h"
#include "GuidePage.h"
#include "global.h"

class QtATM : public QMainWindow
{
	Q_OBJECT

public:
	QtATM(QWidget* parent = Q_NULLPTR);

private slots:
	void onBtnZhClicked();
	void onBtnEnClicked();
	void onSysyemTrayIconClicked(QSystemTrayIcon::ActivationReason);
	void onActionShow();
	void onActionExit();

private:
	Ui::QtATMClass ui;

	//QSettings* m_settings;

	int m_timerId;
	virtual void timerEvent(QTimerEvent*);

	void closeEvent(QCloseEvent*);

	void showTopPage();

	QTranslator* zhTranslator;

public:
	QSystemTrayIcon m_systemTrayIcon;
};
