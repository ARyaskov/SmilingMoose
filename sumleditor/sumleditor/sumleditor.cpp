#include "stdafx.h"
#include "sumleditor.h"


sumleditor::sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне 
}

sumleditor::~sumleditor()
{
	delete diagram;
}
