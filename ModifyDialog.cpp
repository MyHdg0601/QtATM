#include "stdafx.h"
#include "ModifyDialog.h"

ModifyDialog::ModifyDialog(int row, QString num, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_sqlOprtor = new SQLiteOperator(this);

	m_row = row;
	m_oUser = m_sqlOprtor->queryTable(num);
	m_nUser = m_sqlOprtor->queryTable(num);

	ui.edit_name->setText(m_nUser->id);
	ui.edit_num->setText(m_nUser->num);
	ui.lab_money->setText(QString::number(m_nUser->money) + tr(" RMB"));

	connect(ui.edit_num, &QLineEdit::returnPressed, this, &ModifyDialog::onBtnModifyClicked);
	connect(ui.btn_modify, &QPushButton::clicked, this, &ModifyDialog::onBtnModifyClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &ModifyDialog::onBtnBackClicked);
}

void ModifyDialog::onBtnModifyClicked()
{
	QString name = ui.edit_name->text();
	QString num = ui.edit_num->text();

	if (name.length() <= 0) {
		//������������Ϊ�ա�����
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Names cannot be empty."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
	}
	else
	{
		if (!isDigitString(num) || num.length() != 10) {
			//�����˺�Ӧ��Ϊ10λ�����֡�����
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("The account number should be 10 digits."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
			msgBox->exec();
		}
		else
		{
			if (checkNumRepeat(num)) {
				//�����˺��Ѵ��ڣ����������롣�õ�
				QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
					tr("The account already exists. Please re-input."), QMessageBox::Ok, this);
				msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
				msgBox->exec();
			}
			else
			{
				m_nUser->id = name;
				m_nUser->num = num;
				this->close();
				emit modifyInfo(m_row, m_oUser, m_nUser);
			}
		}
	}
}

//����ַ����Ƿ�Ϊ������
bool ModifyDialog::isDigitString(const QString& src) {
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

//����˺��Ƿ��ظ�
bool ModifyDialog::checkNumRepeat(QString& num) {
	if (num == m_nUser->num)//�ų��Լ����ʺ�
	{
		return false;
	}
	return m_sqlOprtor->queryTable(num);
}

void ModifyDialog::onBtnBackClicked()
{
	this->close();
}

ModifyDialog::~ModifyDialog()
{
}
