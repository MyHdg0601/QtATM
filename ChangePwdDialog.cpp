#include "stdafx.h"
#include "ChangePwdDialog.h"

ChangePwdDialog::ChangePwdDialog(User* user, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_user = user;

	connect(ui.ckb_spwd, &QCheckBox::stateChanged, this, &ChangePwdDialog::onCkbChecked);
	connect(ui.edit_rpwd, &QLineEdit::returnPressed, this, &ChangePwdDialog::onBtnChangeClicked);
	connect(ui.btn_change, &QPushButton::clicked, this, &ChangePwdDialog::onBtnChangeClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &ChangePwdDialog::onBtnBackClicked);
}

ChangePwdDialog::~ChangePwdDialog()
{
}

void ChangePwdDialog::onCkbChecked(int state)
{
	if (state == Qt::Unchecked) {
		ui.edit_opwd->setEchoMode(QLineEdit::Password);
		ui.edit_npwd->setEchoMode(QLineEdit::Password);
		ui.edit_rpwd->setEchoMode(QLineEdit::Password);
	}
	else {
		ui.edit_opwd->setEchoMode(QLineEdit::Normal);
		ui.edit_npwd->setEchoMode(QLineEdit::Normal);
		ui.edit_rpwd->setEchoMode(QLineEdit::Normal);
	}
}

void ChangePwdDialog::onBtnChangeClicked()
{
	QString opwd = ui.edit_opwd->text();
	QString npwd = ui.edit_npwd->text();
	QString rpwd = ui.edit_rpwd->text();

	if (opwd != m_user->pwd) {
		//����ԭ����������������
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Input error of original password."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else
	{
		if (!isDigitString(npwd) || npwd.length() != 6) {
			//�������������Ϊ6λ���������롣����
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("The new password must be a 6-bit pure digital password."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
			msgBox->exec();
		}
		else
		{
			if (npwd != rpwd) {
				//���������������벻һ�¡�����
				QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
					tr("The two password entries are inconsistent."), QMessageBox::Ok, this);
				msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
				msgBox->exec();
			}
			else {
				if (npwd == opwd) {
					//��ʾ����������ԭ����һ�£������޸ġ��õ�
					QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Prompt !"),
						tr("The new password is identical to the original one and does not need to be modified."), QMessageBox::Ok, this);
					msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
					msgBox->exec();
				}
				else
				{
					this->close();
					emit changePwd(npwd);
				}
			}
		}
	}
}

void ChangePwdDialog::onBtnBackClicked()
{
	this->close();
}

//����ַ����Ƿ�Ϊ������
bool ChangePwdDialog::isDigitString(const QString& src) {
	int length = src.length();
	if (length <= 0) {
		return false;
	}

	int i = 0;
	for (; i < length; i++) {
		if (src.at(i) < '0' || src.at(i) > '9') {
			break;
		}
	}

	return i >= length;
}