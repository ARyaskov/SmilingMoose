#include "StdAfx.h"
#include "graphwidget.h"

/** Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// Создание сцены

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// Задание метода индексирования сцены
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(0,0,600,600);					// Задание стандартных размеров сцене
	scene->setBackgroundBrush(QColor(140,255,140));

	setScene(scene);									// Задание текущей сцены на виджете

	setDragMode(QGraphicsView::ScrollHandDrag);			// Задать перемещение по сцене "рукой"

	// Задать параметры сцене
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);

	centerOn(0,0);										// Задать позицию обзора сцены 

	scene->addLine(20,20,80,80);
	scene->addLine(80,20,20,80);

}

/** Конструктор по умолчанию. */
GraphWidget::~GraphWidget()
{
	delete scene;
}
