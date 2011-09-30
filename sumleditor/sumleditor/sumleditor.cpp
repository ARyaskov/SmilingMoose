#include "stdafx.h"
#include "sumleditor.h"


sumleditor::sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ���� 

	connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
	connect(ui.actComment,SIGNAL(toggled(bool)),diagram,SLOT(addComment(bool)));
}

sumleditor::~sumleditor()
{
	delete diagram;
}
