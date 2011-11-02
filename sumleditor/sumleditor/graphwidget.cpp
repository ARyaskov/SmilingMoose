#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "objlist.h"

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

	addAxis(1);	// ��������� ���
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

/** �������� �� ����� ��� �� �������� ������. */
void GraphWidget::addAxis(int level)
{
	if (level>0 && level < 10)
	{
		QPen pen = QPen(Qt::DashLine);
		QLine line(0,45*level,600,45*level);
		scene->addLine(line,pen);
	}
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

	// ���� �������� - ����� �������
	switch (currentAct)
	{
		case SELECT:		
			selectItem(mapToScene(event->pos()));
			break;

		case LIFELINE:				 
			initNewLifeline(event);
			break;

		case COMMENT:
			initNewComment(mapToScene(event->pos()));
			break;

		case STOP:
			addStop(mapToScene(event->pos()));
			break;

		case MESSAGE:
			initNewMessage(event);
			break;

		case RECEIVER:
			addMessage(mapToScene(event->pos()));
			break;

		default:
			;
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

/** ���������� �� ����� ����� �����. */
void GraphWidget::addLifeline(Lifeline *lifeline)
{
    lifeline->setPos(lifeline->getX(),lifeline->getY());
    lifeline->setData(Qt::UserRole,"lifeline");

    scene->addItem(lifeline);

    currentAct = SELECT;
    setCursor(Qt::ArrowCursor);

    emit getParentWindow()->selection(true);
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

/** ���������� �� ����� �����������. */
void GraphWidget::addComment(FreeComment *commet)
{
    commet->setPos(commet->getX(),commet->getY());
    commet->setData(Qt::UserRole,"freecomment");

    scene->addItem(commet);

    this->currentAct = SELECT;
    this->setCursor(Qt::ArrowCursor);

    emit getParentWindow()->selection(true);
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
QDomElement GraphWidget::save(QDomDocument & domDoc)
{
	QList<QGraphicsItem*> list = scene->items();
	QDomElement element = domDoc.createElement("project");
	QDomAttr attr = domDoc.createAttribute("name");
	attr.setValue("Project");
	element.setAttributeNode(attr);
	QDomElement diagram = domDoc.createElement("diagram");
	attr = domDoc.createAttribute("total_count");
	attr.setValue(QString::number(list.size()-1));
	diagram.setAttributeNode(attr);
	element.appendChild(saveProperties(domDoc));
	int index = 0; // ������������� ����� �����.

	QDomElement comments = domDoc.createElement("comments");
	attr = domDoc.createAttribute("count");
	// ��� ������: ���������� ������������.
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->data(127).toString() == "freecomment")
		{
			QGraphicsItem* item = list[i];
			FreeComment* comment = (FreeComment*)item;
                        QDomElement el = comment->save(domDoc);
                        comments.appendChild(el);
			index++;
		}
	}
	attr.setValue(QString::number(index));
	comments.setAttributeNode(attr);
	diagram.appendChild(comments);

	index = 0;
	QDomElement lifelines = domDoc.createElement("lifelines");
	// ��� ������: ���������� ����� �����.
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->data(127).toString() == "lifeline")
		{
			QGraphicsItem* item = list[i];
			Lifeline* lifeline = (Lifeline*)item;
			lifeline->id = index;
			lifelines.appendChild(lifeline->save(domDoc, index));
			index++;
		}
	}
	attr.setValue(QString::number(index));
	lifelines.setAttributeNode(attr);
	diagram.appendChild(lifelines);

	element.appendChild(diagram);
	return element;
}

/** ������� ���������� ��������� �� �����. */
void GraphWidget::load(const QDomNode & node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        QDomElement domElement = domNode.toElement();

        if (!domElement.isNull())
        {
            if (domElement.tagName() == "freecomment")
            {
                FreeComment* comment = new FreeComment(this);
                comment->load(domElement);
                addComment(comment);
            }
            else if (domElement.tagName() == "lifeline")
            {
                Lifeline* line = new Lifeline(this);
                line->load(domElement);
                addLifeline(line);
            }
        }

        load(domNode);
        domNode = domNode.nextSibling();
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

/** ���������� ���������� ����� ��. */
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

/** ���������� ���������� ������ �����������. */
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

/** ���������� ���������� ������ ���������. */
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
			addMessage(mapToScene(event->pos()));  // +=+=+=+=+ addToObjList - ��������� ������ ���� �������
															  // ������ ��� ���� ���� ���������� var		  +=+=+=+=+
			//addToObjList(localUI->objectsList, MESSAGE, var);
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
	QGraphicsItem *item = scene->itemAt(point,QTransform());
	Lifeline * line;

	if (currentAct == MESSAGE)
	{	
		if (item!=NULL && item->type() == 0)
		{
			currentItem = item;
			line = (Lifeline*)item;
			line->setSelectedByMessage(true);
			line->update();
			currentAct = RECEIVER;
			sender = line;
		}
	}
    else if (currentAct == RECEIVER)
	{
		if (item!=NULL && item->type() == 0)
		{	
			line = (Lifeline*)currentItem;
			line->setSelectedByMessage(false);
			receiver = (Lifeline*)item;

			Message * msg = new Message(this,sender,receiver);	// ������� ������ ���������
			
			// ������ ����������
			if (sender->pos().x()+45 < receiver->pos().x()+45)	// ���� ����������� ����� �� ����������
				msg->setPos(sender->pos().x()+45, point.y());
			else
				msg->setPos(receiver->pos().x()+45, point.y());

			scene->addItem(msg);

			line->update();
			currentAct = SELECT;

			setCursor(Qt::ArrowCursor);				// ������ ������ ������
			getParentWindow()->setToolbarDefault();
		}
	}
}

QDomElement GraphWidget::saveProperties(QDomDocument & domDoc)
{
	QDomElement prop = domDoc.createElement("properties");
	QDomElement cdateNode = domDoc.createElement("create_date");
	QDomText cdate = domDoc.createTextNode(QDate::currentDate().toString("dd.MM.yyyy"));
	QDomElement authorNode = domDoc.createElement("author");
	QDomText author = domDoc.createTextNode("Author");
	authorNode.appendChild(author);
	cdateNode.appendChild(cdate);
	prop.appendChild(cdateNode);
	prop.appendChild(authorNode);

	return prop;
}
