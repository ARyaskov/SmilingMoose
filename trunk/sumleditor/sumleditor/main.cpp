#include "stdafx.h"
#include "sumleditor.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	sumleditor w;
	w.show();
	return a.exec();
}
