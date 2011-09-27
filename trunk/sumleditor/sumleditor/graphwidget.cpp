#include "StdAfx.h"
#include "graphwidget.h"

/** �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����. */
GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);					// �������� �����

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// ������� ������ �������������� �����
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	
	scene->setSceneRect(0,0,600,600);					// ������� ����������� �������� �����
	scene->setBackgroundBrush(QColor(140,255,140));

	setScene(scene);									// ������� ������� ����� �� �������

	setDragMode(QGraphicsView::ScrollHandDrag);			// ������ ����������� �� ����� "�����"

	// ������ ��������� �����
	setCacheMode(CacheBackground);								
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing,false);
	setTransformationAnchor(AnchorUnderMouse);

	centerOn(0,0);										// ������ ������� ������ ����� 

	scene->addLine(20,20,80,80);
	scene->addLine(80,20,20,80);

}

/** ����������� �� ���������. */
GraphWidget::~GraphWidget()
{
	delete scene;
}
