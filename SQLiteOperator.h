#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>

struct User
{
	QString id;
	QString num;
	QString pwd;
	bool isHighU;
	double money;
};

class SQLiteOperator : public QObject
{
	Q_OBJECT

public:
	SQLiteOperator(QObject* parent);
	~SQLiteOperator();

	bool openDb();
	bool isTableExist();
	void createTable();
	User* queryTable(QString&);
	QList<User*> getAllData();
	void insertSingleData(User*);
	void removeData(User*);
	void updateData(User*);
	void closeDb();

private:
	QSqlDatabase db;
};