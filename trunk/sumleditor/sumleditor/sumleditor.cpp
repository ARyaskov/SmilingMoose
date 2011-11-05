#include "stdafx.h"
#include "sumleditor.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>

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
	connect(ui.actDelete,	SIGNAL(triggered()),	this,	SLOT(deleteObj()));

	// �������� �������� ����
	connect(ui.actionQuit,	SIGNAL(triggered()),	this,	SLOT(slotExit()));
	connect(ui.actionSave,	SIGNAL(triggered()),	this,	SLOT(slotSave()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),	this,	SLOT(slotSaveAs()));
	connect(ui.actionOpen,	SIGNAL(triggered()),	this,	SLOT(slotOpen()));
	connect(ui.actionAboutUs,SIGNAL(triggered()),	this,	SLOT(slotAboutUs()));
	connect(ui.actionAboutQt,SIGNAL(triggered()),	this,	SLOT(slotAboutQt()));
	connect(ui.actionPicture,SIGNAL(triggered()),	this,	SLOT(saveAsPicture()));


	connect(ui.nameEdit,	SIGNAL(textEdited(const QString &)),this,SLOT(nameLEChanged(const QString &)));
	connect(ui.descrEdit,	SIGNAL(textChanged(const QString &)),this,SLOT(descrChanged(const QString &)));

	nameLE_val=new validatorNameLE(this);

	ui.nameEdit->setValidator(nameLE_val);

	ui.actCancel->setEnabled(false);	// ������������ ������ ������

	ui.actSelect->setChecked(true);		// ����� ������ ��������
}

void Sumleditor::nameLEChanged(const QString & text)
{
	qDebug("nameLEChanged");
	if (!ui.nameEdit->hasAcceptableInput())
		blink(ui.nameEdit, normal_color, error_color, 1);

	QPalette palette = ui.nameEdit->palette();


	if (ui.nameEdit->palette().color(QPalette::Base) == attention_color)
	{
		QPalette palette = ui.nameEdit->palette();
		palette.setColor( QPalette::Base, normal_color );
		ui.nameEdit->setPalette(palette);
	}
}

void Sumleditor::descrChanged(const QString & text)
{
	qDebug("descrLEChanged");

	QPalette palette = ui.nameEdit->palette();

	if (ui.descrEdit->palette().color(QPalette::Base) == attention_color)
	{
		QPalette palette = ui.descrEdit->palette();
		palette.setColor( QPalette::Base, normal_color );
		ui.descrEdit->setPalette(palette);
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
	ui.actDelete->setEnabled(false);

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

	if (diagram->getCurrentItem()!= NULL && diagram->getCurrentItem()->type() == 0)
	{
		Lifeline* line = (Lifeline*)diagram->getCurrentItem();
		line->setSelectedByMessage(false);
		line->update();
	}
}

/**
* ����, ������������� ��� ������� ������ ���������� ����� �����.
*/
void Sumleditor::addLifeline()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.nameEdit->setFocus();					// ������ ����� �� ���� ����� ���������

	ui.descrEdit->clear();					    // �������� ���� ����� ��������

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
	setToolbarAdding();

	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.nameEdit->setFocus();					// ������ ����� �� ���� ����� ���������

	ui.descrEdit->clear();					    // �������� ���� ����� ��������
	
	this->diagram->setCurrentAct(MESSAGE);		// �������� - ��������� ����� �����

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// ��������
	fadeInto(ui.nameEdit,  attention_color);	// ������ ���� ���� �����
}

/**
* ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
*/
void Sumleditor::addCreate()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.nameEdit->setFocus();					// ������ ����� �� ���� ����� ���������

	ui.descrEdit->clear();					    // �������� ���� ����� ��������
	
	this->diagram->setCurrentAct(CREATE);		// �������� - ��������� ����� �����

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// ��������
	fadeInto(ui.nameEdit,  attention_color);	// ������ ���� ���� �����
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
	setToolbarAdding();

	diagram->setCurrentAct(STOP);		// �������� - ��������� ����� �����
}

/**
* ����, ������������� ��� ������� ������ ������ �������.
*/
void Sumleditor::addComment()
{
	ui.descrEdit->setFocus();			     	// ������ ����� �� ���� ����� ��������
	ui.nameEdit->clear();						// �������� ���� ����� ����� ���������
	ui.descrEdit->clear();				    	// �������� ���� ����� ��������

	setToolbarAdding();

	this->diagram->setCurrentAct(COMMENT);		// �������� - ��������� ����� �����

	blink(ui.descrEdit, normal_color,  attention_color, 2);	// ��������
	fadeInto(ui.descrEdit,  attention_color);	// ������ ���� ���� �����

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
	filename = QFileDialog::getOpenFileName(this, "������� ����", "seq_001",
		"���� ������� SUMLEditor *.suef;;�������� ����� *.suefd;;XML ���� *.xml");

	qDebug("slotOpen");

        QDomDocument x;
        readFromFile();
}

/** ����, ������������� ��� ������� ������ "���������" � ������� ����. */
void Sumleditor::slotSave()
{
	// ���� ������ �� �������� � �����.
	if (filename == "" || filename == NULL)
	{
		slotSaveAs();
	}

	qDebug("slotSave");
}

/** ����, ������������� ��� ������� ������ "��������� ���..." � ������� ����. */
void Sumleditor::slotSaveAs()
{
	filename = QFileDialog::getSaveFileName(this, "��������� ���...", "seq_001",
    "���� ������� SUMLEditor *.suef;;�������� ����� *.suefd;;XML ���� *.xml");
	
	// ���� ������������ �� ������ ����.
	if (filename == "" || filename == NULL)
	{
		return;
	}

	saveToFile();

	qDebug("slotSaveAs");
}

/** ����, ������������� ��� ������� ������ "������������" � ������� ����. */
void Sumleditor::slotAboutUs()
{
	QMessageBox::about(this, "� SUMLEditor", "��������� ������ � UML ����������� ������������������.\n��������� �������� ���-460:\n��������� �.\n��������� �.\n������ �.\n������� �.");

	qDebug("slotAboutUs");
}

/** ����, ������������� ��� ������� ������ "��������� ��� �����������" � ������� ����. */
void Sumleditor::saveAsPicture()
{
	QString filename = QFileDialog::getSaveFileName(this,QString("��������� ����������� �����"),"seq_001","*.png");

        qDebug("filename:");
        qDebug(filename.toAscii().data());

        QRect rect;

	rect.setCoords(0,0,600,600);
	QImage image(600,600, QImage::Format_ARGB32_Premultiplied);
	image.fill(NULL);
	QPainter painter(&image);
	this->diagram->getScene()->render(&painter,rect,rect,Qt::KeepAspectRatioByExpanding);
	image.save(filename);
}

/** ����, �������������� ������� ������� ��� Del */
void Sumleditor::deleteObj()
{
	this->diagram->removeCurrentItem();
	ui.actDelete->setEnabled(false);
}

/** ������� ������ ��������� � ���� xml ���������. */
void Sumleditor::saveToFile()
{
	QDomDocument doc("project");

	QDomElement element = diagram->save(doc);

	doc.appendChild(element);

	QFile file(filename);

	if (file.open(QIODevice::WriteOnly))
	{	// ���� ��������� �������� �������� �����.
		QTextStream(&file) << doc.toString();
		file.close();
	}
}

/** ������� ���������� ��������� �� xml �����. */
void Sumleditor::readFromFile()
{
    QDomDocument domDoc;
    QFile        file(filename);

    if (file.open(QIODevice::ReadOnly))
    {
		diagram->getScene()->clear();
		diagram->addAxis(1);

        if (domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            diagram->load(domElement);
        }
    }
}
