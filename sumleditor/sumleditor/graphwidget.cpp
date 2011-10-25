#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsItem>

/** �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����. */
GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent)
{
	error_color = QColor(247,115,115);
	warning_color = QColor(243,193,127);
	attention_color = QColor(250,232,139);
	normal_color = QColor(255,255,255);

	scene = new QGraphicsScene(this);					// �������� �����

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);	// ������� ������ �������������� �����
	setOptimizationFlags(QGraphicsView::DontSavePainterState);

	scene->setSceneRect(0,0,600,600);					// ������� ����������� �������� �����

	QPen pen = QPen(Qt::DashLine);						// ��������� ����� �� �����
	scene->addLine(0,45,600,45,pen);

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

	connect(scene, SIGNAL(changed()), this, SLOT(sceneChanged()));

	currentItem = NULL;
}

/** ���������� �� ���������. */
GraphWidget::~GraphWidget()
{
	delete scene;
}

void GraphWidget::sceneChanged()
{
	qDebug("sceneChanged");

}



/** ������� ��������� �������� ����. */
void GraphWidget::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier)			// ���� ��� ���� ������ ������� Ctrl
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

/** ���� ��� ������� ������� �� ������ ����. */
void GraphWidget::mousePressEvent(QMouseEvent * event)
{
	QGraphicsView::mousePressEvent(event);				// ��������� �������

	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;

	// ���� �������� - ����� �������
	if (currentAct == SELECT)			
	{
		selectItem(mapToScene(event->pos()));
	}
	// ���� �������� - �������� ��, ������ � ������� �� ����� 
	else if (currentAct == LIFELINE)
	{
		initNewLifeline(event);
	}
	else if (currentAct == COMMENT)
	{
		initNewComment(mapToScene(event->pos()));
	}
	else if (currentAct == STOP)	// ���� ������� �������� - ���������
	{
		addStop(mapToScene(event->pos()));
	}
	else if (currentAct == MESSAGE)
	{
		initNewMessage(event);
	}
}

/** ������� ���������� ����� ����� �� �����. */
void GraphWidget::addLifeline(QPointF point)
{
	Lifeline* line = new Lifeline(this);			// ������� ���������

	point.setY(30);							// ������ ����������� ���������� �� �
	line->setPos(point);						// ������ ����������
	line->name = getParentWindow()->getUI()->nameEdit->text();		// ������ �����
	line->setData(127,"lifeline");

	scene->addItem(line);						// ��������� �� ����� ���������

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
	comment->setData(127,"freecomment");

	scene->addItem(comment);					// ��������� �� �����

	this->currentAct = SELECT;					// ������ ������� ��������
	this->setCursor(Qt::ArrowCursor);			// ������ ������ ������

	emit getParentWindow()->selection(true);	// �������� ���� ������ �������
}

/** ������� ������ �������. */
void GraphWidget::selectItem(QPointF point)
{
	QGraphicsItem *item;
	Lifeline * line;
	FreeComment * com;

	item = scene->itemAt(point/*event->posF()*/,QTransform());

	if (item!=NULL && item->type()!=6)
		this->mainWnd->getUI()->actDelete->setEnabled(true);
	else
		this->mainWnd->getUI()->actDelete->setEnabled(false);

	// ����� ��������� � �������� �������, ���� ����
	if (currentItem != NULL && item != currentItem)
	{
		// ���� ��� ����� �����
		if (currentItem->type() == 0)
		{
			line = (Lifeline*)currentItem;
			line->setSelected(false);
			line->update();
		}
		else if (currentItem->type() == 1)
		{
			com = (FreeComment*)currentItem;
			com->setSelected(false);
			com->update();
		}

	}

	line = NULL;

	// �������� ����� ������, ������� ��� �������
	if (item != NULL)
	{
		currentItem = item;

		// ���� ��� ����� �����
		if (item->type() == 0)
		{
			line = (Lifeline*)currentItem;
			line->setSelected(true);
			line->update();
		}
		else if (item->type() == 1)
		{
			com = (FreeComment*)currentItem;
			com->setSelected(true);
			com->update();
		}
	}
	line = NULL;
}

/** �������� ������� �� �����. */
void GraphWidget::removeCurrentItem()
{
	scene->removeItem(currentItem);
}

/** ������� ���������� ��������� � ����. */
void GraphWidget::save(QDomDocument & domDoc)
{
	QList<QGraphicsItem*> list = scene->items();
	int index = 0; // ������������� ����� �����.
	// ���� �������� ��������� �����.
	for (int i = 0; i < list.size(); i++)
	{	// ���� ��������� �����������.
		if (list[i]->data(127).toString() == "freecomment")
		{
			QGraphicsItem* item = list.at(i);
			FreeComment* c = (FreeComment*)item;
			c->save(domDoc);
		}
		else if (list[i]->data(127).toString() == "lifeline")
		{	// ���� ��������� ����� �����.
			QGraphicsItem* item = list.at(i);
			Lifeline* ll = (Lifeline*)item;
			ll->save(domDoc, index);
			index++;
		}
	}
}

/** ���������� ��������� ����� ������� �����. */ 
void GraphWidget::addStop(QPointF point)
{
	QGraphicsItem *item = scene->itemAt(point,QTransform());

	if (item!=NULL && item->type() == 0)
	{
		Lifeline * line = (Lifeline*)item;
		line->setEnded();
		line->update();

		currentAct = SELECT;					// ������ ������� ��������
		setCursor(Qt::ArrowCursor);				// ������ ������ ������
		getParentWindow()->setToolbarDefault();
	}
}

void GraphWidget::initNewLifeline(QMouseEvent * event)
{
	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;

	if (localUI->nameEdit->text().length())
	{
		meta.action = LIFELINE;
		meta.name = localUI->nameEdit->text();
		meta.id = QString("LifeLine-"+localUI->nameEdit->text());
		var.setValue(meta);
		if (existDublicate(localUI->objectsList, var ))
		{	// ���� ��� ���������, �� ���������
			QMessageBox::information(this, "Attention!", "This name already exists!");
			fadeInto(localUI->nameEdit, error_color);		// ��������� ��������� ���� ����� �����
			localUI->nameEdit->setFocus();
			QGraphicsView::mouseReleaseEvent(event);
		}
		else
		{
			addLifeline(mapToScene(event->pos()));	// ��������� ������ �� �����, ������ ����������� Y
			addToObjList(localUI->objectsList,LIFELINE, var);
		}
	}else
	{
		blink(localUI->nameEdit,normal_color, error_color,2);		    // ������ �������
		localUI->nameEdit->setFocus();									// ������������ �� ������ �����
	}
}

void GraphWidget::initNewComment(QPointF point)
{
	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;

	if (localUI->descrEdit->toPlainText().length())
	{
		meta.action = COMMENT;
		meta.name = localUI->nameEdit->text();
		meta.desc = localUI->descrEdit->toPlainText();
		meta.id = QString("Comment-"+localUI->nameEdit->text());
		var.setValue(meta);
		
		//if (existDublicate(localUI->objectsList, var ))	// ���� ��� ���������
		//	QMessageBox::information(this, "Attention!", "This comment already exist on scene!");
		//else
		
		addComment(point);	// ��������� ������ �� �����, ������ ����������� Y
		addToObjList(localUI->objectsList,COMMENT, var);
	}
	else
	{
		blink(localUI->descrEdit,normal_color, error_color,2);		    // ������ �������
		localUI->descrEdit->setFocus();									// ������������ �� ������ ��������
	}
}

void GraphWidget::initNewMessage(QMouseEvent * event)
{
	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;

	if (localUI->nameEdit->text().length())
	{
		meta.action = MESSAGE;
		meta.name = localUI->nameEdit->text();
		meta.id = QString("Message-"+localUI->nameEdit->text());
		var.setValue(meta);
		if (existDublicate(localUI->objectsList, var ))
		{	// ���� ��� ���������, �� ���������
			QMessageBox::information(this, "Attention!", "This name already exists!");
			fadeInto(localUI->nameEdit, error_color);		// ��������� ��������� ���� ����� �����
			localUI->nameEdit->setFocus();
			QGraphicsView::mouseReleaseEvent(event);
		}
		else
		{
			addMessage(mapToScene(event->pos()));
			addToObjList(localUI->objectsList, MESSAGE, var);
		}
	}
	else
	{
		blink(localUI->nameEdit,normal_color, error_color,2);		    // ������ �������
		localUI->nameEdit->setFocus();									// ������������ �� ������ �����
	}
}

/** ���������� ��������� ����� ������� �����. */
void GraphWidget::addMessage(QPointF point)
{
	
}