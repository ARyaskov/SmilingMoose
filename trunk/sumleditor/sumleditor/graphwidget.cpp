#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>

/** �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// �������� �����

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// ������� ������ �������������� �����
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(-300,-300,600,600);				// ������� ����������� �������� �����
	scene->setBackgroundBrush(QColor(200,240,240));		// ������� ����� ����
	setScene(scene);									// ������� ������� ����� �� �������

	setDragMode(QGraphicsView::ScrollHandDrag);			// ������ ����������� �� ����� "�����"

	// ������ ��������� �����
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);
	centerOn(0,0);										// ������ ������� ������ ����� 

	this->currentAct = SELECT;							// ������� �������� - ����� ������ �� �����
	this->mainWnd = (Sumleditor*)parent;				// �������� ��������� �� ������� ����
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





























///** �������� ���� ���������� ������� �� �����. */
//void GraphWidget::addObject(bool isChecked)
//{
//	if (isChecked) // ���� "�������" ������.
//	{
//		//LifeLine *testLine = new LifeL8-w58-ybw75yine(this);
//		//FreeComment *testCom = new FreeComment(this);	// ������� ������ �����������
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
///** ���� ���������� ����������� �� �����. */
//void GraphWidget::addComment()
//{
//	FreeComment *testCom = new FreeComment(this);	// ������� ������ �����������
//
//	scene->addItem(testCom);						// ��������� ��� �� �����
//
//	lastItem = (FreeComment*)testCom;				// ��������� ��������� ��������� ������
//}