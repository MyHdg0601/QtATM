#include "stdafx.h"
#include "HUserPage.h"

HUserPage::HUserPage(User* user, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_user = user;

	m_sqlOprtor = new SQLiteOperator(this);

	setTimeWord();
	setListData();

	connect(ui.btn_modify, &QPushButton::clicked, this, &HUserPage::onBtnModifyClicked);
	connect(ui.btn_correct, &QPushButton::clicked, this, &HUserPage::onBtnCorrectClicked);
	connect(ui.btn_reset, &QPushButton::clicked, this, &HUserPage::onBtnRestPwdClicked);
	connect(ui.btn_cacnt, &QPushButton::clicked, this, &HUserPage::onBtnDestoryClicked);
	connect(ui.btn_search, &QPushButton::clicked, this, &HUserPage::onBtnSearchClicked);
	connect(ui.btn_cus, &QPushButton::clicked, this, &HUserPage::onBtnCUsClicked);
	connect(ui.btn_logout, &QPushButton::clicked, this, &HUserPage::onBtnLogoutClicked);
}

HUserPage::~HUserPage()
{
}

//����ʱ�������ʺ���
void HUserPage::setTimeWord()
{
	QTime time = QTime::currentTime();
	int hour = time.hour();
	QString words = "";
	if (hour >= 0 && hour < 5) {
		words = tr("Good evening");//���Ϻ�
	}
	if (hour >= 5 && hour < 11) {
		words = tr("Good morning");//���Ϻ�
	}
	if (hour >= 11 && hour < 13) {
		words = tr("Good noon");//�����
	}
	if (hour >= 13 && hour < 19) {
		words = tr("Good afternoon");//�����
	}
	if (hour >= 19 && hour < 24) {
		words = tr("Good evening");//���Ϻ�
	}
	words += tr(", ") + m_user->id;
	ui.lab_name->setText(words);
}

//���һ������
void HUserPage::addItem(QString name, QString num, QString money)
{
	QListWidgetItem* item = new QListWidgetItem();
	item->setData(Qt::UserRole, name);
	item->setData(Qt::UserRole + 1, num);
	item->setData(Qt::UserRole + 2, money);
	ui.list_users->addItem(item);
}

//��ȡ�����ñ������
void HUserPage::setListData()
{
	m_allData = m_sqlOprtor->getAllData();
	QList<User*>::iterator i;
	for (i = m_allData.begin(); i != m_allData.end(); i++)
	{
		User* user = *i;
		if (!user->isHighU) {
			addItem(user->id, user->num, QString::number(user->money));
		}
	}
	ui.list_users->setItemDelegate(new UserItemDrawer(ui.list_users));
}

//��Ϣ�޸�
void HUserPage::onBtnModifyClicked()
{
	QListWidgetItem* item = ui.list_users->currentItem();
	int row = ui.list_users->currentRow();
	QString num = item->data(Qt::UserRole + 1).toString();
	ModifyDialog* modifyDialog = new ModifyDialog(row, num, this);
	connect(modifyDialog, &ModifyDialog::modifyInfo, this, &HUserPage::onModifyInfo);
	modifyDialog->exec();
}

void HUserPage::onModifyInfo(int row, User* oUser, User* user)
{
	m_sqlOprtor->removeData(oUser);
	m_sqlOprtor->insertSingleData(user);
	QListWidgetItem* item = ui.list_users->takeItem(row);
	if (item) {
		delete item;
	}
	addItem(user->id, user->num, QString::number(user->money));

	//��Ϣ�޸ĳɹ�
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("Information has been modified."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//���У��
void HUserPage::onBtnCorrectClicked()
{
	QListWidgetItem* item = ui.list_users->currentItem();
	int row = ui.list_users->currentRow();
	QString num = item->data(Qt::UserRole + 1).toString();
	CorrectDialog* correctDialog = new CorrectDialog(row, m_sqlOprtor->queryTable(num), this);
	connect(correctDialog, &CorrectDialog::correctBalance, this, &HUserPage::onCorrectBalance);
	correctDialog->exec();
}

void HUserPage::onCorrectBalance(int row, User* user)
{
	m_sqlOprtor->updateData(user);
	QListWidgetItem* item = ui.list_users->takeItem(row);
	if (item) {
		delete item;
	}
	addItem(user->id, user->num, QString::number(user->money));

	//���У���ɹ�
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("Balance has been corrected."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//��������
void HUserPage::onBtnRestPwdClicked()
{
	QListWidgetItem* item = ui.list_users->currentItem();
	QString num = item->data(Qt::UserRole + 1).toString();
	RestPwdDialog* restPwdDialog = new RestPwdDialog(m_sqlOprtor->queryTable(num), this);
	connect(restPwdDialog, &RestPwdDialog::restPassword, this, &HUserPage::onRestPassword);
	restPwdDialog->exec();
}

void HUserPage::onRestPassword(User* user)
{
	m_sqlOprtor->updateData(user);
	//�������óɹ�
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
		tr("Password Reset."), QMessageBox::Ok, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
	msgBox->exec();
}

//�����ʻ�
void HUserPage::onBtnDestoryClicked()
{
	QListWidgetItem* item = ui.list_users->currentItem();
	QString num = item->data(Qt::UserRole + 1).toString();
	int row = ui.list_users->currentRow();
	User* user = m_sqlOprtor->queryTable(num);
	//���棡�˲���������ת�������ؿ��Ǻ������ע�� ȡ��
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Warning !"),
		user->id + tr(" about to be destroyed.This operation is irreversible! please consider carefully and continue."), QMessageBox::Ok | QMessageBox::Cancel, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Destory"));
	msgBox->button(QMessageBox::Cancel)->setText(tr("Cancel"));
	if (msgBox->exec() == QMessageBox::Ok) {
		m_sqlOprtor->removeData(user);
		QListWidgetItem* dItem = ui.list_users->takeItem(row);
		delete user, dItem;

		//�ɹ����ʻ����ٳɹ������û���Ҫ�ٴ�ʹ�ã�����ʾ������ע�ᡣ�õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("The account was destroyed successfully. If the user needs to use it again, please prompt him to re-join."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
	else
	{
		delete user;
	}
}

//�����û�
void HUserPage::onBtnSearchClicked()
{
	SearchDialog* searchDialog = new SearchDialog(this);
	connect(searchDialog, &SearchDialog::searchUser, this, &HUserPage::onSearchUser);
	searchDialog->exec();
}

void HUserPage::onSearchUser(QString num)
{
	User* user = m_sqlOprtor->queryTable(num);
	if (!user || user->isHighU) {
		//�����û�δ�ҵ����õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Error !"),
			tr("User not found."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();
	}
	else
	{
		int n = ui.list_users->count();
		for (int i = 0; i < n; i++) {
			QListWidgetItem* item = ui.list_users->item(i);
			if (num == item->data(Qt::UserRole + 1)) {
				item->setSelected(true);
				break;
			}
		}
	}
}

//���ٴ˹����ʻ�
void HUserPage::onBtnCUsClicked()
{
	//���棡�˲���������ת�������ؿ��Ǻ������ע�� ȡ��
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Warning !"),
		tr("This operation is irreversible! please consider carefully and continue."), QMessageBox::Ok | QMessageBox::Cancel, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Destory"));
	msgBox->button(QMessageBox::Cancel)->setText(tr("Cancel"));
	if (msgBox->exec() == QMessageBox::Ok) {
		m_sqlOprtor->removeData(m_user);

		//�ɹ��������ʻ������٣������ٴ�ʹ�ã�������ע�ᡣ�õ�
		QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Success !"),
			tr("The management account has been destroyed. If you need to use it again, please re-join."), QMessageBox::Ok, this);
		msgBox->button(QMessageBox::Ok)->setText(tr("Ok"));
		msgBox->exec();

		topPage = PAGE_GUIDE;

		this->close();

		guidePage->show();
	}
}

//�ǳ�
void HUserPage::onBtnLogoutClicked()
{
	//��ʾ��ȷ���˳���¼��ȷ�� ȡ��
	QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, tr("Prompt !"),
		tr("Confirm logout?"), QMessageBox::Ok | QMessageBox::Cancel, this);
	msgBox->button(QMessageBox::Ok)->setText(tr("Logout"));
	msgBox->button(QMessageBox::Cancel)->setText(tr("Cancel"));
	if (msgBox->exec() == QMessageBox::Ok) {
		topPage = PAGE_GUIDE;

		this->close();

		guidePage->show();
	}
}

void HUserPage::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}