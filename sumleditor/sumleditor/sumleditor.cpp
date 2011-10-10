#include "stdafx.h"
#include "sumleditor.h"
#include <QTextCodec>
#include <QMessageBox>

Sumleditor::Sumleditor(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	ui.setupUi(this);

    error_color = QColor(247,115,115);
	warning_color = QColor(243,193,127);
    attention_color = QColor(250,232,139);
    normal_color = QColor(255,255,255);

 	// ����������� �������� �����
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// �������� ����� 
	ui.gridLayout->addWidget(diagram);		// ��������� ��� �� grid layout � ������� ����

	// �������� �������
	connect(ui.actComment,	SIGNAL(triggered()),	this,	SLOT(addComment()));
	connect(ui.actCreate,	SIGNAL(triggered()),	this,	SLOT(addCreate()));
	connect(ui.actDestroy,	SIGNAL(triggered()),	this,	SLOT(addDelete()));
	connect(ui.actLifeline,	SIGNAL(triggered()),	this,	SLOT(addLifeline()));
	connect(ui.actMessage,	SIGNAL(triggered()),	this,	SLOT(addMessage()));
	connect(ui.actReply,	SIGNAL(triggered()),	this,	SLOT(addReply()));
	connect(ui.actSelect,	SIGNAL(toggled(bool)),	this,	SLOT(selection(bool)));
	connect(ui.actStop,		SIGNAL(triggered()),	this,	SLOT(addStop()));
    connect(ui.actCancel,	SIGNAL(triggered()),	this,	SLOT(cancel()));

	// �������� �������� ����
	connect(ui.actionQuit,	SIGNAL(triggered()),	this,	SLOT(slotExit()));
	connect(ui.actionSave,	SIGNAL(triggered()),	this,	SLOT(slotSave()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),	this,	SLOT(slotSaveAs()));
	connect(ui.actionOpen,	SIGNAL(triggered()),	this,	SLOT(slotOpen()));
	connect(ui.actionAboutUs,SIGNAL(triggered()),	this,	SLOT(slotAboutUs()));
	connect(ui.actionAboutQt,SIGNAL(triggered()),	this,	SLOT(slotAboutQt()));

	connect(ui.nameEdit,	SIGNAL(textEdited(const QString &)),this,SLOT(nameLEChanged(const QString &)));

	nameLE_val=new validatorNameLE(this);

	ui.nameEdit->setValidator(nameLE_val);

	ui.actCancel->setEnabled(false);	// ������������ ������ ������

	ui.actSelect->setChecked(true);		// ����� ������ ��������
}

void Sumleditor::nameLEChanged(const QString & text)
{
	qDebug("nameLEChanged");
	if (!ui.nameEdit->hasAcceptableInput())
		blink(ui.nameEdit, QColor(255,255,255), error_color, 1);

	QPalette palette = ui.nameEdit->palette();
    
 
	if (ui.nameEdit->palette().color(QPalette::Base) == attention_color)
	{
		QPalette palette = ui.nameEdit->palette();
        palette.setColor( QPalette::Base, normal_color );
		ui.nameEdit->setPalette(palette);
	}
 }

Sumleditor::~Sumleditor()
{
	delete nameLE_val;
	delete diagram;
}

/** ������� ����������� ���������� �������. */
void Sumleditor::setToolbarDefault()
{
	ui.actSelect->setChecked(true);					// �������� ������� ������

	ui.actCancel->setEnabled(false);				// ������������ ������ ������

	ui.actComment->setEnabled(true);			
	ui.actCreate->setEnabled(true);				
	ui.actDestroy->setEnabled(true);			
	ui.actLifeline->setEnabled(true);			
	ui.actMessage->setEnabled(true);			
	ui.actSelect->setEnabled(true);				
	ui.actReply->setEnabled(true);				
	ui.actStop->setEnabled(true);

	ui.actComment->setChecked(false);			
	ui.actCreate->setChecked(false);				
	ui.actDestroy->setChecked(false);			
	ui.actLifeline->setChecked(false);			
	ui.actMessage->setChecked(false);						
	ui.actReply->setChecked(false);				
	ui.actStop->setChecked(false);	
}

/** ������� ���������� ������� ��� �������� ����������. */
void Sumleditor::setToolbarAdding()
{
	ui.actSelect->setChecked(false);			// �������� ������� ������
	ui.actCancel->setEnabled(true);				// ������������ ������ ������

	ui.actComment->setEnabled(false);			
	ui.actCreate->setEnabled(false);				
	ui.actDestroy->setEnabled(false);			
	ui.actLifeline->setEnabled(false);			
	ui.actMessage->setEnabled(false);			
	ui.actSelect->setEnabled(false);				
	ui.actReply->setEnabled(false);				
	ui.actStop->setEnabled(false);		
}

/**
* ����, ������������� ��� ������� ������ ������ �������.
*/
void Sumleditor::selection(bool checked)
{
	setToolbarDefault();
	fadeInto(ui.nameEdit, QColor(255,255,255));		// ��������� ��������� ���� ����� �����
}


/**
* ����, ������������� ��� ������� �� Cancel, ���� ��  Esc
*/
void Sumleditor::cancel()
{
    setToolbarDefault();							// ����������� �������� �������

	this->diagram->setCursor(Qt::ArrowCursor);		// ������ ������
	this->diagram->setCurrentAct(SELECT);			// ������ ������� ���������

	fadeInto(ui.nameEdit, normal_color);		// ��������� ��������� ���� ����� �����

	ui.nameEdit->clear();							// �������� ���� ����� ����� ���������
}

/**
* ����, ������������� ��� ������� ������ ���������� ����� �����.
*/
void Sumleditor::addLifeline()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.nameEdit->setFocus();					// ������ ����� �� ���� ����� ���������

	this->diagram->setCursor(Qt::CrossCursor);	// ������ ������
	this->diagram->setCurrentAct(LIFELINE);		// �������� - ��������� ����� �����

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// ��������
	fadeInto(ui.nameEdit,  attention_color);	// ������ ���� ���� �����
    
	ui.statusBar->showMessage(QString("���������� ����� �����. ������� ��� � �������� �� ������ ����� �� �����."));
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
	ui.nameEdit->setFocus();				// ������ ����� �� ���� ����� ���������
	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.descrEdit->clear();					// �������� ���� ����� ����� ���������
	
	setToolbarAdding();
	
	this->diagram->setCursor(Qt::CrossCursor);	// ������ ������
	this->diagram->setCurrentAct(COMMENT);		// �������� - ��������� ����� �����

	blink(ui.nameEdit, QColor(255,255,255),  attention_color, 2);	// ��������
	fadeInto(ui.nameEdit,  attention_color);	// ������ ���� ���� �����

	ui.statusBar->showMessage(QString("���������� �����������. ������� ��� � �������� �� ������ ����� �� �����."));
}

/** ���� ������������� ��� ������� ������ "�����" � ������� ����. */
void Sumleditor::slotExit()
{
	if (QMessageBox::Yes == QMessageBox::question(this,QString("�������� ���������"),
			QString("������� ���������?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::No) )
		exit(0);
}

/** ���� ������������� ��� ������� ������ "� Qt" � ������� ����. */
void Sumleditor::slotAboutQt()
{
	QMessageBox::aboutQt(this,"� Qt");
}

/** ����, ������������� ��� ������� ������ "�������" � ������� ����. */
void Sumleditor::slotOpen()
{
	qDebug("slotOpen");
}

/** ����, ������������� ��� ������� ������ "���������" � ������� ����. */
void Sumleditor::slotSave()
{
	qDebug("slotSave");
}

/** ����, ������������� ��� ������� ������ "��������� ���..." � ������� ����. */
void Sumleditor::slotSaveAs()
{
	qDebug("slotSaveAs");
}

/** ����, ������������� ��� ������� ������ "������������" � ������� ����. */
void Sumleditor::slotAboutUs()
{
	qDebug("slotAboutUs");
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