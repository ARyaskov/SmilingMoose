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
}

Sumleditor::~Sumleditor()
{
	delete diagram;
}

/**
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::selection()
{
	qDebug("selection");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления линии жизни.
 */
void Sumleditor::setLifelineAdding()
{
	qDebug("setLifelineAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения.
 */
void Sumleditor::setMessageAdding()
{
	qDebug("setMessageAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
 */
void Sumleditor::setCreateAdding()
{
	qDebug("setCreateAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
 */
void Sumleditor::setDeleteAdding()
{
	qDebug("setDeleteAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
 */
void Sumleditor::setReplyAdding()
{
	qDebug("setReplyAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::setStopAdding()
{
	qDebug("setStopAdding");
}

/**
 * Слот, срабатывающий при нажатии кнопки выбора объекта.
 */
void Sumleditor::setCommentAdding()
{
	qDebug("setCommentAdding");
}





























//connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
//connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
//connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(setComment()));

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