#pragma once

#include <QWidget>

#include "ui_JoinPage.h"
#include "GuidePage.h"
#include "SQLiteOperator.h"
#include "global.h"

class JoinPage : public QWidget
{
	Q_OBJECT

public:
	JoinPage(QWidget* parent = Q_NULLPTR);
	~JoinPage();

private slots:
	void onCkbChecked(int);
	void onRadHighUToggled(bool);
	void onBtnJoinClicked();
	void onBtnBackClicked();

private:
	Ui::JoinPage ui;

	SQLiteOperator* m_sqlOprtor;

	bool isDigitString(const QString&);
	bool checkInformation(QString&, QString&, QString&, QString&, bool, QString&);
	bool checkNumRepeat(QString&);

	void closeEvent(QCloseEvent*);
};
