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

 	// Подключение русского языка
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне

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

	ui.actCancel->setEnabled(false);	// Декативируем кнопку отмены

	ui.actSelect->setChecked(true);		// Режим выбора объектов
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

/** Задание стандартных параметров тулбара. */
void Sumleditor::setToolbarDefault()
{
	ui.actSelect->setChecked(true);					// Нажимаем текущую кнопку

	ui.actCancel->setEnabled(false);				// Декативируем кнопку отмены

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

/** Задание параметров тулбара для процесса добавления. */
void Sumleditor::setToolbarAdding()
{
	ui.actSelect->setChecked(false);			// Нажимаем текущую кнопку
	ui.actCancel->setEnabled(true);				// Декативируем кнопку отмены

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
* Слот, срабатывающий при нажатии кнопки выбора объекта.
*/
void Sumleditor::selection(bool checked)
{
	setToolbarDefault();
	fadeInto(ui.nameEdit, QColor(255,255,255));		// Отключаем раскраску поля ввода имени
}


/**
* Слот, срабатывающий при нажатии на Cancel, либо на  Esc
*/
void Sumleditor::cancel()
{
    setToolbarDefault();							// Стандартные свойства тулбара

	this->diagram->setCursor(Qt::ArrowCursor);		// Задаем курсор
	this->diagram->setCurrentAct(SELECT);			// Задать текущее состояние

	fadeInto(ui.nameEdit, QColor(255,255,255));		// Отключаем раскраску поля ввода имени

	ui.nameEdit->clear();							// Очистить поле ввода имени заогловка
}

/**
* Слот, срабатывающий при нажатии кнопки добавления линии жизни.
*/
void Sumleditor::addLifeline()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// Очистить поле ввода имени заогловка
	ui.nameEdit->setFocus();					// Задать фокус на поле ввода заголовка

	this->diagram->setCursor(Qt::CrossCursor);	// Задаем курсор
	this->diagram->setCurrentAct(LIFELINE);		// Действие - добавляем линию жизни

	blink(ui.nameEdit, QColor(255,255,255),  attention_color, 2);	// Помигать
	fadeInto(ui.nameEdit,  attention_color);	// Задаем цвет полю ввода

	ui.statusBar->showMessage(QString("Добавление линии жизни. Введите имя и кликните на нажное место на сцене."));
}

/**
* Слот, срабатывающий при нажатии кнопки добавления сообщения.
*/
void Sumleditor::addMessage()
{
	qDebug("addMessage");
}

/**
* Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
*/
void Sumleditor::addCreate()
{
	qDebug("addCreate");
}

/**
* Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
*/
void Sumleditor::addDelete()
{
	qDebug("addDelete");
}

/**
* Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
*/
void Sumleditor::addReply()
{
	qDebug("addReply");
}

/**
* Слот, срабатывающий при нажатии кнопки выбора объекта.
*/
void Sumleditor::addStop()
{
	qDebug("addStop");
}

/**
* Слот, срабатывающий при нажатии кнопки выбора объекта.
*/
void Sumleditor::addComment()
{
	ui.nameEdit->setFocus();				// Задать фокус на поле ввода заголовка
	ui.nameEdit->clear();						// Очистить поле ввода имени заогловка
	ui.descrEdit->clear();					// Очистить поле ввода имени заогловка
	
	setToolbarAdding();
	
	this->diagram->setCursor(Qt::CrossCursor);	// Задаем курсор
	this->diagram->setCurrentAct(COMMENT);		// Действие - добавляем линию жизни

	blink(ui.nameEdit, QColor(255,255,255),  attention_color, 2);	// Помигать
	fadeInto(ui.nameEdit,  attention_color);	// Задаем цвет полю ввода

	ui.statusBar->showMessage(QString("Добавление комментария. Введите имя и кликните на нажное место на сцене."));
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