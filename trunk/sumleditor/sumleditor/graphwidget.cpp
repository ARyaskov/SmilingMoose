#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>

/** Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне. */
GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent)
{
	error_color = QColor(247,115,115);
	warning_color = QColor(243,193,127);
	attention_color = QColor(250,232,139);
	normal_color = QColor(255,255,255);

	scene = new QGraphicsScene(this);					// Создание сцены

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// Задание метода индексирования сцены
	setOptimizationFlags(QGraphicsView::DontSavePainterState);

	scene->setSceneRect(0,0,600,600);				// Задание стандартных размеров сцене
	//scene->addLine(-600,-150,600,-150);
	//scene->setBackgroundBrush(QColor(200,240,240));		// Задание цвета фона
	setScene(scene);									// Задание текущей сцены на виджете

	//setDragMode(QGraphicsView::ScrollHandDrag);			// Задать перемещение по сцене "рукой"

	// Задать параметры сцене
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);
	centerOn(0,0);										// Задать позицию обзора сцены 

	this->currentAct = SELECT;							// Текущее действие - выбор объкта на сцене
	this->mainWnd = (Sumleditor*)parent;				// Получаем указатель на главное окно
}

/** Деструктор по умолчанию. */
GraphWidget::~GraphWidget()
{
	delete scene;
}

/** Событие прокрутки колесика мыши. */
void GraphWidget::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, -event->delta() / 480.0));
}

/** Функция масштабирования сцены. */
void GraphWidget::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.1 || factor > 50)
		return;

	scale(scaleFactor, scaleFactor);
}

/** Слот для события перемещения указателя мыши. */
void GraphWidget::mouseMoveEvent(QMouseEvent * event)
{

}

/** Слот для события нажатия на кнопку мыши. */
void GraphWidget::mousePressEvent(QMouseEvent * event)
{
	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;
	localUI->nameEdit->setToolTip("");
	// Если действие - выбор объекта
	if (currentAct == SELECT)			
	{
		// Пока ничего не делаем
	}
	// Если действие - добавить ЛЖ, строка с текстом не пуста 
	else if (currentAct == LIFELINE && localUI->nameEdit->text().length())
	{
		meta.action = LIFELINE;
		meta.name = localUI->nameEdit->text();
		meta.id = QString("LifeLine-"+localUI->nameEdit->text());
		var.setValue(meta);
		if (existDublicate(localUI->objectsList, var ))
		{	// Если нет дубликата, то добавляем
			localUI->nameEdit->setToolTip("This name already exists!");
			fadeInto(localUI->nameEdit, error_color);		// Отключаем раскраску поля ввода имени
		}
		else
		{
			addLifeline(mapToScene(event->x(), 30));	// Добавляем объект на сцену, задаем стандартный Y
			addToObjList(localUI->objectsList,LIFELINE,QVariant(localUI->nameEdit->text()));
		}
	}
	else if (currentAct == COMMENT && localUI->nameEdit->text().length())
	{
		meta.action = COMMENT;
		meta.name = localUI->nameEdit->text();
		meta.id = QString("Comment-"+localUI->nameEdit->text());
		var.setValue(meta);
		if (existDublicate(localUI->objectsList, var ))	// Если нет дубликата
			QMessageBox::information(this, "Attention!", "This lifeline already exist on scene!");
		else
			addComment(mapToScene(event->x(), event->y()));	// Добавляем объект на сцену, задаем стандартный Y
	}
	else
	{
		blink(localUI->nameEdit,normal_color, error_color,2);		// Мигаем красным
		localUI->nameEdit->setFocus();									// Фокусируемся на строке имени
	}
}

/** Функция добавления линии жизни на сцену. */
void GraphWidget::addLifeline(QPointF point)
{
	Header* header = new Header(this);			// Создаем заголовок
	Lifeline * lifeline = new Lifeline(this);	// Задаем линию жизни

	point.setY(30);							// Задаем стандартную коорлинату по У
	header->setPos(point);						// Задаем координаты
	header->name = getParentWindow()->getUI()->nameEdit->text();		// Задаем текст

	//scene->addItem(header);						// Добавляем на сцену зкголовок

	// Задаем координаты линии
	point.setX(point.x()+45);					
	point.setY(point.y()+32);
	lifeline->setPos(point);

	//scene->addItem(lifeline);					// Добавляем линию на сцену
	
	this->currentAct = SELECT;					// Задаем текущее действие
	this->setCursor(Qt::ArrowCursor);			// Задаем ноовый курсор

	emit getParentWindow()->selection(true);	// Вызываем слот выбора объекта
	
	// Группируем объекты
	QList<QGraphicsItem *>lifelineList;			// Контейнер объктов

	lifelineList.append(header);
	lifelineList.append(lifeline);
	
	scene->createItemGroup(lifelineList);
}

/** Добавление на сцену комментария. */
void GraphWidget::addComment(QPointF point)
{
	FreeComment* comment = new FreeComment(this);		// Создаем объект
	comment->setPos(point);								// Задаем координаты
	comment->text = getParentWindow()->getUI()->descrEdit->toPlainText();	// Задаем комментарию текст

	scene->addItem(comment);					// Добавляем на сцену

	this->currentAct = SELECT;					// Задаем текущее действие
	this->setCursor(Qt::ArrowCursor);			// Задаем ноовый курсор

	emit getParentWindow()->selection(true);	// Вызываем слот выбора объекта
}


















//	if (this->currentAct!=SELECT)
//if (!getParentWindow()->getUI()->mainToolBar->isEnabled())
//	this->viewport()->setCursor(Qt::CrossCursor);
//else	
//	this->viewport()->setCursor(Qt::ArrowCursor);


//QList<QGraphicsItem *>lifelineList;
//QGraphicsItemGroup *lifelineGroup;

//if (getParentWindow()->getUI()->nameEdit->text().length())
//{
//	if (!getParentWindow()->getUI()->mainToolBar->isEnabled()){
//		if (existDublicate())
//		{
//			QMessageBox::information(this, "Attention!", "This Header already exist on scene!");
//		}
//		else
//		{
//			Header* lifeline1 = new Header(this);
//			lifeline1->setPos(mapToScene(event->x(), event->y()) );

//			scene->addItem(lifeline1);

//			lifelineList.append(lifeline1);

//			getParentWindow()->getUI()->mainToolBar->setEnabled(true);
//			getParentWindow()->getUI()->actCancel->setEnabled(false);
//			fadeInto(getParentWindow()->getUI()->nameEdit, QColor(255,255,255));
//		}
//	}else
//	{
//		blink(getParentWindow()->getUI()->mainToolBar,QColor(255,255,255), attention_color, 1);
//	}
//}
//else
//{
//	blink(getParentWindow()->getUI()->nameEdit,QColor(255,255,255), error_color,2);
//}


///** ТЕСТОВЫЙ слот добавления объекта на сцену. */
//void GraphWidget::addObject(bool isChecked)
//{
//	if (isChecked) // Если "утопили" кнопку.
//	{
//		//Header *testLine = new LifeL8-w58-ybw75yine(this);
//		//FreeComment *testCom = new FreeComment(this);	// СОздаем объект комментария
//	
//		//QList<QGraphicsItem *>list;
//		//list.append(testLine);
//		//list.append(testCom);
//		//
//		//QGraphicsItemGroup * qwe = scene->createItemGroup(list);
//		//qwe->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
//	//	scene->addItem(testLine);
//	//	scene->addItem(testCom);
//	}
//}
//
///** Слот добавления комментария на сцену. */
//void GraphWidget::addComment()
//{
//	FreeComment *testCom = new FreeComment(this);	// СОздаем объект комментария
//
//	scene->addItem(testCom);						// Добавляем его на сцену
//
//	lastItem = (FreeComment*)testCom;				// Сохраняем последний созданный объект
//}