#include "stdafx.h"
#include "sumleditor.h"

#include <QTextCodec>

Sumleditor::Sumleditor(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	ui.setupUi(this);

    error_color = QColor(247,115,115);
	warning_color = QColor(243,193,127);
    attention_color = QColor(250,232,139);

 	// ����������� �������� �����
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ����

	connect(ui.actComment,	SIGNAL(triggered()),	this,	SLOT(addComment()));
	connect(ui.actCreate,	SIGNAL(triggered()),	this,	SLOT(addCreate()));
	connect(ui.actDestroy,	SIGNAL(triggered()),	this,	SLOT(addDelete()));
	connect(ui.actLifeline,	SIGNAL(triggered()),	this,	SLOT(addLifeline()));
	connect(ui.actMessage,	SIGNAL(triggered()),	this,	SLOT(addMessage()));
	connect(ui.actReply,	SIGNAL(triggered()),	this,	SLOT(addReply()));
	connect(ui.actSelect,	SIGNAL(toggled(bool)),	this,	SLOT(selection(bool)));
	connect(ui.actStop,		SIGNAL(triggered()),	this,	SLOT(addStop()));
    connect(ui.actCancel,	SIGNAL(triggered()),	this,	SLOT(cancel()));

	connect(ui.nameEdit,	SIGNAL(textEdited(const QString &)),this,SLOT(nameLEChanged(const QString &)));

	nameLE_val=new validatorNameLE(this);


	ui.nameEdit->setValidator(nameLE_val);

	ui.actCancel->setEnabled(false);

	
}

void Sumleditor::cancel()
{
    ui.mainToolBar->setEnabled(true);
}

void Sumleditor::nameLEChanged(const QString & text)
{
	if (!ui.nameEdit->hasAcceptableInput())
		blink(ui.nameEdit, QColor(255,255,255), error_color, 1);
}

Sumleditor::~Sumleditor()
{
	delete nameLE_val;
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
void Sumleditor::addLifeline()
{
	qDebug("addLifeline");
	ui.mainToolBar->setEnabled(false);
	//ui.actCancel->setEnabled(true);
	ui.nameEdit->clear();

	blink(ui.nameEdit, QColor(255,255,255),  attention_color, 2);
	fadeInto(ui.nameEdit,  attention_color);
	
}

/**
* ����, ������������� ��� ������� ������ ���������� ���������.
*/
void Sumleditor::addMessage()
{
	qDebug("addMessage");
}

/**
* ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
*/
void Sumleditor::addCreate()
{
	qDebug("addCreate");
}

/**
* ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
*/
void Sumleditor::addDelete()
{
	qDebug("addDelete");
}

/**
* ����, ������������� ��� ������� ������ ���������� ����������� ���������.
*/
void Sumleditor::addReply()
{
	qDebug("addReply");
}

/**
* ����, ������������� ��� ������� ������ ������ �������.
*/
void Sumleditor::addStop()
{
	qDebug("addStop");
}

/**
* ����, ������������� ��� ������� ������ ������ �������.
*/
void Sumleditor::addComment()
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