#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>

/** �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// �������� �����

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// ������� ������ �������������� �����
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(0,0,600,600);					// ������� ����������� �������� �����
	//scene->setBackgroundBrush(QColor(140,255,140));	// ������� ����� ����

	setScene(scene);									// ������� ������� ����� �� �������

	setDragMode(QGraphicsView::ScrollHandDrag);			// ������ ����������� �� ����� "�����"

	// ������ ��������� �����
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);

	centerOn(0,0);										// ������ ������� ������ ����� 
}

/** ���������� �� ���������. */
GraphWidget::~GraphWidget()
{
	delete scene;
}

/** ������� ��������� �������� ����. */
void GraphWidget::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, -event->delta() / 480.0));
}

/** ������� ��������������� �����. */
void GraphWidget::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.1 || factor > 50)
		return;

	scale(scaleFactor, scaleFactor);
}

/** �������� ���� ���������� ������� �� �����. */
void GraphWidget::addObject(bool isChecked)
{
	if (isChecked) // ���� "�������" ������.
	{
		LifeLine *testLine = new LifeLine(this);
		scene->addItem(testLine);
	}
}

	/** ���� ���������� ����������� �� �����. */
void GraphWidget::addComment(bool isChecked)
{
	if (isChecked) // ���� "�������" ������.
	{
		FreeComment *testLine = new FreeComment(this);
		scene->addItem(testLine);
	}
}