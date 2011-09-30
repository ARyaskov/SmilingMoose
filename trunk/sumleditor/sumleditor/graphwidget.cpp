#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>

/** Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// Создание сцены

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// Задание метода индексирования сцены
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(0,0,600,600);					// Задание стандартных размеров сцене
	//scene->setBackgroundBrush(QColor(140,255,140));	// Задание цвета фона

	setScene(scene);									// Задание текущей сцены на виджете

	setDragMode(QGraphicsView::ScrollHandDrag);			// Задать перемещение по сцене "рукой"

	// Задать параметры сцене
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);

	centerOn(0,0);										// Задать позицию обзора сцены 
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

/** ТЕСТОВЫЙ слот добавления объекта на сцену. */
void GraphWidget::addObject(bool isChecked)
{
	if (isChecked) // Если "утопили" кнопку.
	{
		LifeLine *testLine = new LifeLine(this);
		scene->addItem(testLine);
	}
}

	/** Слот добавления комментария на сцену. */
void GraphWidget::addComment(bool isChecked)
{
	if (isChecked) // Если "утопили" кнопку.
	{
		FreeComment *testLine = new FreeComment(this);
		scene->addItem(testLine);
	}
}