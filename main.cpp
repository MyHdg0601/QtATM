#include "stdafx.h"
#include "QtATM.h"
#include "global.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	qtATM = new QtATM(NULL);
	qtATM->show();
	return a.exec();
}
