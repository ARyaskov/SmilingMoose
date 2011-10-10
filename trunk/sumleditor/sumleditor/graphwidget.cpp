#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>

/** �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����. */
GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent)
{
    error_color = QColor(247,115,115);
	warning_color = QColor(243,193,127);
    attention_color = QColor(250,232,139);

	scene = new QGraphicsScene(this);					// �������� �����

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// ������� ������ �������������� �����
	setOptimizationFlags(QGraphicsView::DontSavePainterState);

	scene->setSceneRect(-300,-300,600,600);				// ������� ����������� �������� �����
	scene->addLine(-600,-150,600,-150);
	scene->setBackgroundBrush(QColor(200,240,240));		// ������� ����� ����
	setScene(scene);									// ������� ������� ����� �� �������

	//setDragMode(QGraphicsView::ScrollHandDrag);			// ������ ����������� �� ����� "�����"

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

/** ���� ��� ������� ����������� ��������� ����. */
void GraphWidget::mouseMoveEvent(QMouseEvent * event)
{

}

/** ���� ��� ������� ������� �� ������ ����. */
void GraphWidget::mousePressEvent(QMouseEvent * event)
{
	// ���� �������� - ����� �������
	if (currentAct == SELECT)			
	{
		// ���� ������ �� ������
	}
	// ���� �������� - �������� ��, ������ � ������� �� ����� 
	else if (currentAct == LIFELINE && getParentWindow()->getUI()->nameEdit->text().length())
	{
		if (existDublicate())	// ���� ��� ���������
			QMessageBox::information(this, "Attention!", "This lifeline already exist on scene!");
		else
			addLifeline(mapToScene(event->x(), 30));	// ��������� ������ �� �����, ������ ����������� Y
	}
	else if (currentAct == COMMENT && getParentWindow()->getUI()->nameEdit->text().length())
	{
		if (existDublicate())	// ���� ��� ���������
			QMessageBox::information(this, "Attention!", "This lifeline already exist on scene!");
		else
			addComment(mapToScene(event->x(), event->y()));	// ��������� ������ �� �����, ������ ����������� Y
	}
	else
	{
		blink(getParentWindow()->getUI()->nameEdit,QColor(255,255,255), error_color,2);		// ������ �������
		getParentWindow()->getUI()->nameEdit->setFocus();									// ������������ �� ������ �����
	}
}

/** ������� ���������� ����� ����� �� �����. */
void GraphWidget::addLifeline(QPointF point)
{
	Header* lifeline = new Header(this);		// ������� ������
	point.setY(-180);
	lifeline->setPos(point);					// ������ ����������

	lifeline->name = getParentWindow()->getUI()->nameEdit->text();

	scene->addItem(lifeline);					// ��������� �� �����

	this->currentAct = SELECT;					// ������ ������� ��������
	this->setCursor(Qt::ArrowCursor);			// ������ ������ ������

	emit getParentWindow()->selection(true);	// �������� ���� ������ �������

	
}

/** ���������� �� ����� �����������. */
void GraphWidget::addComment(QPointF point)
{
	FreeComment* comment = new FreeComment(this);		// ������� ������
	comment->setPos(point);								// ������ ����������
	comment->text = getParentWindow()->getUI()->descrEdit->toPlainText();	// ������ ����������� �����

	scene->addItem(comment);					// ��������� �� �����

	this->currentAct = SELECT;					// ������ ������� ��������
	this->setCursor(Qt::ArrowCursor);			// ������ ������ ������

	emit getParentWindow()->selection(true);	// �������� ���� ������ �������
}

bool GraphWidget::existDublicate()
{
	// Implement this later
	return false;
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


///** �������� ���� ���������� ������� �� �����. */
//void GraphWidget::addObject(bool isChecked)
//{
//	if (isChecked) // ���� "�������" ������.
//	{
//		//Header *testLine = new LifeL8-w58-ybw75yine(this);
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