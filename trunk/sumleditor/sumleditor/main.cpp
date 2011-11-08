#include "stdafx.h"
#include "volatile.h"
#include "sumleditor.h"
#include "uexception.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	try
	{
		QApplication a(argc, argv);
		Sumleditor w;
		w.setWindowState(w.windowState() ^ Qt::WindowMaximized);	// Развернуть окно на весь экран
		w.show();
		return a.exec();
	}
	catch(SUMLEditorException ex)
	{
		writeErrors(ex.message());
		return 1;
	}
	catch(...)
	{
		writeErrors((new SUMLEditorException())->message());
		return 1;
	}
}
