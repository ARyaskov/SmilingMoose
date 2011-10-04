#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>

/** Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// Создание сцены

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// Задание метода индексирования сцены
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(-300,-300,600,600);				// Задание стандартных размеров сцене
	scene->setBackgroundBrush(QColor(200,240,240));		// Задание цвета фона
	setScene(scene);									// Задание текущей сцены на виджете

	setDragMode(QGraphicsView::ScrollHandDrag);			// Задать перемещение по сцене "рукой"

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





























///** ТЕСТОВЫЙ слот добавления объекта на сцену. */
//void GraphWidget::addObject(bool isChecked)
//{
//	if (isChecked) // Если "утопили" кнопку.
//	{
//		//LifeLine *testLine = new LifeL8-w58-ybw75yine(this);
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