#include "stdafx.h"
#include "sumleditor.h"

#include <QTextCodec>

Sumleditor::Sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// ����������� �������� �����
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ����

	connect(ui.actComment,	SIGNAL(toggled(bool)),	this,	SLOT(addComment(bool)));
	connect(ui.actCreate,	SIGNAL(toggled(bool)),	this,	SLOT(addCreate(bool)));
	connect(ui.actDestroy,	SIGNAL(toggled(bool)),	this,	SLOT(addDelete(bool)));
	connect(ui.actLifeline,	SIGNAL(toggled(bool)),	this,	SLOT(addLifeline(bool)));
	connect(ui.actMessage,	SIGNAL(toggled(bool)),	this,	SLOT(addMessage(bool)));
	connect(ui.actReply,	SIGNAL(toggled(bool)),	this,	SLOT(addReply(bool)));
	connect(ui.actSelect,	SIGNAL(toggled(bool)),	this,	SLOT(selection(bool)));
	connect(ui.actStop,		SIGNAL(toggled(bool)),	this,	SLOT(addStop(bool)));
}

Sumleditor::~Sumleditor()
{
	delete diagram;
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::selection(bool checked)
{
	if (checked)
		qDebug("selection ON");
	else
		qDebug("selection OFF");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ����� �����.
 */
void Sumleditor::addLifeline(bool checked)
{
	qDebug("addLifeline");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ���������.
 */
void Sumleditor::addMessage(bool checked)
{
	qDebug("addMessage");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
 */
void Sumleditor::addCreate(bool checked)
{
	qDebug("addCreate");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
 */
void Sumleditor::addDelete(bool checked)
{
	qDebug("addDelete");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ����������� ���������.
 */
void Sumleditor::addReply(bool checked)
{
	qDebug("addReply");
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::addStop(bool checked)
{
	qDebug("addStop");
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::addComment(bool checked)
{
	qDebug("addComment");
}





























//connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
//connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
//connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(addComment()));

///** ���� ��� ���������� ����������� �� �����. */
//void sumleditor::addComment(bool isChecked)
//{
//	diagram->setCursor(Qt::ArrowCursor);
//
//	diagram->addComment();		// ��������� ������ �� �����
//
//	ui.descrEdit->setFocus();	// ������������ �� ��������� ����
//
//	// ��������� ��������� � ���������.
//	ui.statusBar->showMessage(QString("������� ����� �����������."));
//}
//
///** ���� ��� ������� ������ �����������. */
//void sumleditor::setComment()
//{
//	// ����� ���� ��������� ��������� �������, ������ ��� �����������
//	FreeComment * com = (FreeComment*)diagram->lastItem;	
//
//	com->text = ui.descrEdit->toPlainText();	// ������ ��� �����
//	
//	com->update();								// �������������� ���
//}