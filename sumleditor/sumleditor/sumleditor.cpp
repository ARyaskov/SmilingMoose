#include "stdafx.h"
#include "sumleditor.h"


sumleditor::sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне 

	connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
	connect(ui.actComment,SIGNAL(toggled(bool)),diagram,SLOT(addComment(bool)));
}

sumleditor::~sumleditor()
{
	delete diagram;
}
