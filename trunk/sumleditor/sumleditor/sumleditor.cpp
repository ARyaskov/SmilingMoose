#include "stdafx.h"
#include "sumleditor.h"


sumleditor::sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ���� 
}

sumleditor::~sumleditor()
{
	delete diagram;
}
