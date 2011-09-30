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

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне 

	connect(ui.actLifeline,SIGNAL(toggled(bool)),diagram,SLOT(addObject(bool)));
	connect(ui.actComment,SIGNAL(toggled(bool)),this,SLOT(addComment(bool)));
	connect(ui.descrEdit,SIGNAL(textChanged()),this,SLOT(setComment()));
	
}

sumleditor::~sumleditor()
{
	delete diagram;
}

/** Слот для добавления комментария на сцену. */
void sumleditor::addComment(bool isChecked)
{
	diagram->addComment();		// Добавляем объект на сцену

	ui.descrEdit->setFocus();	// Фокусируемся на текстовом поле

	// Добавляем подсказку в статусбар.
	ui.statusBar->showMessage(QString("Вводите текст комментария."));
}

/** Слот для задания текста комментарию. */
void sumleditor::setComment()
{
	// Берем пока последний созданный элемент, сейчас это комментарий
	FreeComment * com = (FreeComment*)diagram->lastItem;	

	com->text = ui.descrEdit->toPlainText();	// Задаем ему текст
	
	com->update();								// Перерисовываем его
}