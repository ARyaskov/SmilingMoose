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
}

Sumleditor::~Sumleditor()
{
	delete diagram;
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::selection()
{
	qDebug("selection");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ����� �����.
 */
void Sumleditor::setLifelineAdding()
{
	qDebug("setLifelineAdding");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ���������.
 */
void Sumleditor::setMessageAdding()
{
	qDebug("setMessageAdding");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
 */
void Sumleditor::setCreateAdding()
{
	qDebug("setCreateAdding");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
 */
void Sumleditor::setDeleteAdding()
{
	qDebug("setDeleteAdding");
}

/**
 * ����, ������������� ��� ������� ������ ���������� ����������� ���������.
 */
void Sumleditor::setReplyAdding()
{
	qDebug("setReplyAdding");
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::setStopAdding()
{
	qDebug("setStopAdding");
}

/**
 * ����, ������������� ��� ������� ������ ������ �������.
 */
void Sumleditor::setCommentAdding()
{
	qDebug("setCommentAdding");
}





























//connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
//connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
//connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(setComment()));

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