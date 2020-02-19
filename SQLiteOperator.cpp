#include "stdafx.h"
#include "SQLiteOperator.h"

SQLiteOperator::SQLiteOperator(QObject* parent)
	: QObject(parent)
{
	if (QSqlDatabase::contains("qt_sql_default_connection")) {
		db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else {
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName("QtATM.db");
	}

	openDb();
	if (!isTableExist()) {
		createTable();
	}
}

SQLiteOperator::~SQLiteOperator()
{
	db.close();
}

//创建数据库并建立连接 
bool SQLiteOperator::openDb()
{
	if (!db.open()) {
		return false;
	}
	return true;
}

//判断数据表是否存在
bool SQLiteOperator::isTableExist()
{
	QSqlQuery query;
	query.exec("SELECT * FROM SQLITE_MASTER WHERE NAME = 'USERSINFORMATION'");
	return query.next();
}

//创建数据表
void SQLiteOperator::createTable()
{
	QSqlQuery query;
	QString str = QString("CREATE TABLE USERSINFORMATION (")
		+ QString("NUM TEXT PRIMARY KEY NOT NULL,")
		+ QString("ID TEXT NOT NULL,")
		+ QString("PWD TEXT NOT NULL,")
		+ QString("ISHU INT NOT NULL,")
		+ QString("MONEY REAL NOT NULL)");
	query.exec(str);
}

//查询和显示结果 
User* SQLiteOperator::queryTable(QString& num)
{
	QSqlTableModel model;
	model.setTable("USERSINFORMATION");
	model.setFilter(QString("num = '") + num + QString("'"));
	if (model.select()) {
		if (model.rowCount() <= 0) {
			return NULL;
		}
		User* user = new User();
		QSqlRecord record = model.record(0);
		user->num = record.value("NUM").toString();
		user->id = record.value("ID").toString();
		user->pwd = record.value("PWD").toString();
		user->isHighU = record.value("ISHU").toBool();
		user->money = record.value("MONEY").toDouble();
		return user;
	}
	return NULL;
}

//返回所有数据
QList<User*> SQLiteOperator::getAllData()
{
	QList<User*> allData;
	QSqlTableModel model;
	model.setTable("USERSINFORMATION");
	if (model.select()) {
		if (model.rowCount() <= 0) {
			return allData;
		}
		else
		{
			for (int i = 0; i < model.rowCount(); i++)
			{
				User* user = new User();
				QSqlRecord record = model.record(i);
				user->num = record.value("NUM").toString();
				user->id = record.value("ID").toString();
				user->pwd = record.value("PWD").toString();
				user->isHighU = record.value("ISHU").toBool();
				user->money = record.value("MONEY").toDouble();
				allData.append(user);
			}
		}
	}
	return allData;
}

//插入单条数据    
void SQLiteOperator::insertSingleData(User* user)
{
	QSqlQuery query;
	query.prepare("INSERT INTO USERSINFORMATION VALUES (:NUM, :ID, :PWD, :ISHU, :MONEY)");
	query.bindValue(":NUM", user->num);
	query.bindValue(":ID", user->id);
	query.bindValue(":PWD", user->pwd);
	query.bindValue(":ISHU", user->isHighU);
	query.bindValue(":MONEY", user->money);
	query.exec();
}

//删除数据   
void SQLiteOperator::removeData(User* user)
{
	QSqlTableModel model;
	model.setTable("USERSINFORMATION");
	model.setFilter(QString("num = '") + user->num + QString("'"));
	if (model.select()) {
		if (model.rowCount() == 1) {
			model.removeRows(0, 1);
			model.submitAll();
		}
	}
}

//修改数据 
void SQLiteOperator::updateData(User* user)
{
	QSqlTableModel model;
	model.setTable("USERSINFORMATION");
	model.setFilter(QString("num = '") + user->num + QString("'"));
	if (model.select()) {
		if (model.rowCount() == 1) {
			QSqlRecord record = model.record(0);
			record.setValue("NUM", user->num);
			record.setValue("ID", user->id);
			record.setValue("PWD", user->pwd);
			record.setValue("ISHU", user->isHighU);
			record.setValue("MONEY", user->money);
			model.setRecord(0, record);
			model.submitAll();
		}
	}
}

//关闭数据库  
void SQLiteOperator::closeDb()
{
	db.close();
}