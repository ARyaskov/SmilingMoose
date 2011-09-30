#include "stdafx.h"
#include "sumleditor.h"

#include <QTextCodec>


sumleditor::sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Codec for Russian Language connect
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");//*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ���� 

	connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
	connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
	connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(setComment()));
	
}

sumleditor::~sumleditor()
{
	delete diagram;
}

/** ���� ��� ���������� ����������� �� �����. */
void sumleditor::addComment(bool isChecked)
{
	diagram->addComment();		// ��������� ������ �� �����

	ui.descrEdit->setFocus();	// ������������ �� ��������� ����

	// ��������� ��������� � ���������.
	ui.statusBar->showMessage(QString("������� ����� �����������."));
}

/** ���� ��� ������� ������ �����������. */
void sumleditor::setComment()
{
	// ����� ���� ��������� ��������� �������, ������ ��� �����������
	FreeComment * com = (FreeComment*)diagram->lastItem;	

	com->text = ui.descrEdit->toPlainText();	// ������ ��� �����
	
	com->update();								// �������������� ���
}