#include "stdafx.h"
#include "sumleditor.h"

#include <QTextCodec>

Sumleditor::Sumleditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Подключение русского языка
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне

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
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::selection(bool checked)
{
	if (checked)
		qDebug("selection ON");
	else
		qDebug("selection OFF");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления линии жизни.
 */
void Sumleditor::addLifeline(bool checked)
{
	qDebug("addLifeline");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения.
 */
void Sumleditor::addMessage(bool checked)
{
	qDebug("addMessage");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
 */
void Sumleditor::addCreate(bool checked)
{
	qDebug("addCreate");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
 */
void Sumleditor::addDelete(bool checked)
{
	qDebug("addDelete");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
 */
void Sumleditor::addReply(bool checked)
{
	qDebug("addReply");
}

/**
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::addStop(bool checked)
{
	qDebug("addStop");
}

/**
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::addComment(bool checked)
{
	qDebug("addComment");
}





























//connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
//connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
//connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(addComment()));

///** Слот для добавления комментария на сцену. */
//void sumleditor::addComment(bool isChecked)
//{
//	diagram->setCursor(Qt::ArrowCursor);
//
//	diagram->addComment();		// Добавляем объект на сцену
//
//	ui.descrEdit->setFocus();	// Фокусируемся на текстовом поле
//
//	// Добавляем подсказку в статусбар.
//	ui.statusBar->showMessage(QString("Вводите текст комментария."));
//}
//
///** Слот для задания текста комментарию. */
//void sumleditor::setComment()
//{
//	// Берем пока последний созданный элемент, сейчас это комментарий
//	FreeComment * com = (FreeComment*)diagram->lastItem;	
//
//	com->text = ui.descrEdit->toPlainText();	// Задаем ему текст
//	
//	com->update();								// Перерисовываем его
//}