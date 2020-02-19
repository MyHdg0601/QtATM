#include "stdafx.h"
#include "JoinPage.h"

JoinPage::JoinPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_sqlOprtor = new SQLiteOperator(this);

	connect(ui.ckb_spwd, &QCheckBox::stateChanged, this, &JoinPage::onCkbChecked);
	connect(ui.edit_rpwd, &QLineEdit::returnPressed, this, &JoinPage::onBtnJoinClicked);
	connect(ui.edit_hpwd, &QLineEdit::returnPressed, this, &JoinPage::onBtnJoinClicked);
	connect(ui.rad_highu, &QRadioButton::toggled, this, &JoinPage::onRadHighUToggled);
	connect(ui.btn_join, &QPushButton::clicked, this, &JoinPage::onBtnJoinClicked);
	connect(ui.btn_back, &QPushButton::clicked, this, &JoinPage::onBtnBackClicked);

	ui.edit_hpwd->setVisible(false);
	ui.lab_hpwd->setVisible(false);
}

JoinPage::~JoinPage()
{
}

void JoinPage::onCkbChecked(int state)
{
	if (state == Qt::Unchecked) {
		ui.edit_pwd->setEchoMode(QLineEdit::Password);
		ui.edit_rpwd->setEchoMode(QLineEdit::Password);
	}
	else {
		ui.edit_pwd->setEchoMode(QLineEdit::Normal);
		ui.edit_rpwd->setEchoMode(QLineEdit::Normal);
	}
}

void JoinPage::onRadHighUToggled(bool checked)
{
	if (checked) {
		ui.edit_hpwd->setVisible(true);
		ui.lab_hpwd->setVisible(true);
	}
	else {
		ui.edit_hpwd->setVisible(false);
		ui.lab_hpwd->setVisible(false);
	}
}

void JoinPage::onBtnJoinClicked()
{
	QString id = ui.edit_id->text();
	QString num = ui.edit_num->text();
	QString pwd = ui.edit_pwd->text();
	QString rpwd = ui.edit_rpwd->text();
	bool isHighU = ui.rad_highu->isChecked();
	QString hpwd = ui.edit_hpwd->text();

	if (checkInformation(id, num, pwd, rpwd, isHighU, hpwd)) {
		if (isHighU) {
			//�ɹ����𾴵ĸ߼�����Ա����ӭ���롣�õ�
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
				tr("Dear Senior manager, welcome to join us."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
			msgBox->exec();
		}
		else {
			//�ɹ����𾴵��û�����л����ע�ᡣ�õ�
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
				tr("Dear user, thank you for your join."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
			msgBox->exec();
		}

		User* user = new User();
		user->num = num;
		user->id = id;
		user->pwd = pwd;
		user->isHighU = isHighU;
		user->money = 0;
		m_sqlOprtor->insertSingleData(user);

		topPage = PAGE_GUIDE;

		this->close();

		guidePage->show();
	}
}

//���ע����Ϣ�Ƿ���Ϲ���
bool JoinPage::checkInformation(QString& id, QString& num, QString& pwd, QString& rpwd, bool isHighU, QString& hpwd) {
	if (id.length() <= 0) {
		//������������Ϊ�ա�����
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("Names cannot be empty."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
		return false;
	}
	if (!isDigitString(num) || num.length() != 10) {
		//�����˺�Ӧ��Ϊ10λ�����֡�����
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The account number should be 10 digits."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
		return false;
	}
	if (checkNumRepeat(num)) {
		//�����˺��Ѵ��ڣ������������ֱ�ӵ�¼���õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The account already exists. Please re-input or login directly."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
		return false;
	}
	if (!isDigitString(pwd) || pwd.length() != 6) {
		//��������Ӧ��Ϊ6λ�����֡�����
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The password should be 6-bit pure digits."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
		return false;
	}
	if (rpwd != pwd) {
		//���������������벻һ�¡�����
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
			tr("The two password entries are inconsistent."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
		msgBox->exec();
		return false;
	}
	if (isHighU) {
		if (hpwd != "0601") {
			//���󣡹�������У�鲻ͨ��������
			QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, tr("Error !"),
				tr("The MnagPwd check failed."), QMessageBox::Ok, this);
			msgBox->button(QMessageBox::Ok)->setText(tr("Re-input"));
			msgBox->exec();
			return false;
		}
	}

	return true;
}

//����ַ����Ƿ�Ϊ������
bool JoinPage::isDigitString(const QString& src) {
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
bool JoinPage::checkNumRepeat(QString& num) {
	return m_sqlOprtor->queryTable(num);
}

void JoinPage::onBtnBackClicked()
{
	topPage = PAGE_GUIDE;

	this->close();

	guidePage->show();
}


void JoinPage::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}