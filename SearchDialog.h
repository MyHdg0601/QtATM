#pragma once

#include <QDialog>
#include "ui_SearchDialog.h"

class SearchDialog : public QDialog
{
	Q_OBJECT

public:
	SearchDialog(QWidget *parent = Q_NULLPTR);
	~SearchDialog();

signals:
	void searchUser(QString);

private slots:
	void onBtnSearchClicked();
	void onBtnBackClicked();

private:
	Ui::SearchDialog ui;

	bool isDigitString(const QString&);
};
