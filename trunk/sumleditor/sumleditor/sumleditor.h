#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_sumleditor.h"

class sumleditor : public QMainWindow
{
	Q_OBJECT

public:
	sumleditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~sumleditor();

private:
	Ui::sumleditorClass ui;
};

#endif // SUMLEDITOR_H
