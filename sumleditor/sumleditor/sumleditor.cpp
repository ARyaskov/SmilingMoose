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

	// Подключение русского языка
	QTextCodec *codec = QTextCodec::codecForName/*("UTF-8");*/("CP1251");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);

	diagram = new GraphWidget(this);		// Создание сцены 
	ui.gridLayout->addWidget(diagram);		// Помещение его на grid layout в главном окне

	// Коннекты тулбара
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

	// Коннекты главного меню
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

	ui.actCancel->setEnabled(false);	// Декативируем кнопку отмены

	ui.actSelect->setChecked(true);		// Режим выбора объектов
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
	ui.actDelete->setEnabled(false);

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

	fadeInto(ui.nameEdit, normal_color);		// Отключаем раскраску поля ввода имени

	ui.nameEdit->clear();							// Очистить поле ввода имени заогловка

	if (diagram->getCurrentItem()!= NULL && diagram->getCurrentItem()->type() == 0)
	{
		Lifeline* line = (Lifeline*)diagram->getCurrentItem();
		line->setSelectedByMessage(false);
		line->update();
	}
}

/**
* Слот, срабатывающий при нажатии кнопки добавления линии жизни.
*/
void Sumleditor::addLifeline()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// Очистить поле ввода имени заголовка
	ui.nameEdit->setFocus();					// Задать фокус на поле ввода заголовка

	ui.descrEdit->clear();					    // Очистить поле ввода описания

	this->diagram->setCurrentAct(LIFELINE);		// Действие - добавляем линию жизни

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// Помигать
	fadeInto(ui.nameEdit,  attention_color);	// Задаем цвет полю ввода

	ui.statusBar->showMessage(QString("Добавление линии жизни. Введите имя и кликните на нажное место на сцене."));
}

/**
* Слот, срабатывающий при нажатии кнопки добавления сообщения.
*/
void Sumleditor::addMessage()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// Очистить поле ввода имени заголовка
	ui.nameEdit->setFocus();					// Задать фокус на поле ввода заголовка

	ui.descrEdit->clear();					    // Очистить поле ввода описания
	
	this->diagram->setCurrentAct(MESSAGE);		// Действие - добавляем линию жизни

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// Помигать
	fadeInto(ui.nameEdit,  attention_color);	// Задаем цвет полю ввода
}

/**
* Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
*/
void Sumleditor::addCreate()
{
	setToolbarAdding();

	ui.nameEdit->clear();						// Очистить поле ввода имени заголовка
	ui.nameEdit->setFocus();					// Задать фокус на поле ввода заголовка

	ui.descrEdit->clear();					    // Очистить поле ввода описания
	
	this->diagram->setCurrentAct(CREATE);		// Действие - добавляем линию жизни

	blink(ui.nameEdit, normal_color,  attention_color, 2);	// Помигать
	fadeInto(ui.nameEdit,  attention_color);	// Задаем цвет полю ввода
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
	setToolbarAdding();

	diagram->setCurrentAct(STOP);		// Действие - добавляем линию жизни
}

/**
* Слот, срабатывающий при нажатии кнопки выбора объекта.
*/
void Sumleditor::addComment()
{
	ui.descrEdit->setFocus();			     	// Задать фокус на поле ввода описания
	ui.nameEdit->clear();						// Очистить поле ввода имени заогловка
	ui.descrEdit->clear();				    	// Очистить поле ввода описания

	setToolbarAdding();

	this->diagram->setCurrentAct(COMMENT);		// Действие - добавляем линию жизни

	blink(ui.descrEdit, normal_color,  attention_color, 2);	// Помигать
	fadeInto(ui.descrEdit,  attention_color);	// Задаем цвет полю ввода

	ui.statusBar->showMessage(QString("Добавление комментария. Введите имя и кликните на нужное место на сцене."));
}

/** Слот срабатывающий при нажатии кнопки "Выход" в главном меню. */
void Sumleditor::slotExit()
{
	if (QMessageBox::Yes == QMessageBox::question(this,QString("Закрытие программы"),
		QString("Закрыть программу?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::No) )
		exit(0);
}

/** Слот срабатывающий при нажатии кнопки "О Qt" в главном меню. */
void Sumleditor::slotAboutQt()
{
	QMessageBox::aboutQt(this,"О Qt");
}

/** Слот, срабатывающий при нажатии кнопки "Открыть" в главном меню. */
void Sumleditor::slotOpen()
{
	filename = QFileDialog::getOpenFileName(this, "Открыть файл", "seq_001",
		"Файл проекта SUMLEditor *.suef;;Черновая схема *.suefd;;XML файл *.xml");

	qDebug("slotOpen");

        QDomDocument x;
        readFromFile();
}

/** Слот, срабатывающий при нажатии кнопки "Сохранить" в главном меню. */
void Sumleditor::slotSave()
{
	// Если проект не привязан к файлу.
	if (filename == "" || filename == NULL)
	{
		slotSaveAs();
	}

	qDebug("slotSave");
}

/** Слот, срабатывающий при нажатии кнопки "Сохранить как..." в главном меню. */
void Sumleditor::slotSaveAs()
{
	filename = QFileDialog::getSaveFileName(this, "Сохранить как...", "seq_001",
    "Файл проекта SUMLEditor *.suef;;Черновая схема *.suefd;;XML файл *.xml");
	
	// Если пользователь не выбрал файл.
	if (filename == "" || filename == NULL)
	{
		return;
	}

	saveToFile();

	qDebug("slotSaveAs");
}

/** Слот, срабатывающий при нажатии кнопки "Разработчики" в главном меню. */
void Sumleditor::slotAboutUs()
{
	QMessageBox::about(this, "О SUMLEditor", "Программа работы с UML диаграммами последовательности.\nВыполнили студенты ИВТ-460:\nГригорьев В.\nНавроцкий М.\nРясков А.\nСоколов С.");

	qDebug("slotAboutUs");
}

/** Слот, срабатывающий при нажатии кнопки "Сохранить как изображение" в главном меню. */
void Sumleditor::saveAsPicture()
{
	QString filename = QFileDialog::getSaveFileName(this,QString("Сохранить изображение сцены"),"seq_001","*.png");

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

/** Слот, обрабатывающий нажатие удалить или Del */
void Sumleditor::deleteObj()
{
	this->diagram->removeCurrentItem();
	ui.actDelete->setEnabled(false);
}

/** Функция записи диаграммы в файл xml структуры. */
void Sumleditor::saveToFile()
{
	QDomDocument doc("project");

	QDomElement element = diagram->save(doc);

	doc.appendChild(element);

	QFile file(filename);

	if (file.open(QIODevice::WriteOnly))
	{	// Если произошло успешное открытие файла.
		QTextStream(&file) << doc.toString();
		file.close();
	}
}

/** Функция считывания диаграммы из xml файла. */
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
