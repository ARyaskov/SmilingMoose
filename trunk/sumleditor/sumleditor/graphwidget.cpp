#include "StdAfx.h"
#include "graphwidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsItem>

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

	scene->setSceneRect(0,0,600,600);					// Задание стандартных размеров сцене

	QPen pen = QPen(Qt::DashLine);						// Добавляем линию на сцену
	scene->addLine(0,45,600,45,pen);

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

	connect(scene, SIGNAL(changed()), this, SLOT(sceneChanged()));

	currentItem = NULL;
}

/** Деструктор по умолчанию. */
GraphWidget::~GraphWidget()
{
	delete scene;
}

void GraphWidget::sceneChanged()
{
	qDebug("sceneChanged");

}



/** Событие прокрутки колесика мыши. */
void GraphWidget::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier)			// Если при этом нажата клавиша Ctrl
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

/** Слот для события нажатия на кнопку мыши. */
void GraphWidget::mousePressEvent(QMouseEvent * event)
{
	QGraphicsView::mousePressEvent(event);				// Повторяем событие

	Ui::SumleditorClass* localUI = getParentWindow()->getUI();
	ElementMetaInfo meta;
	QVariant var;

	// Если действие - выбор объекта
	if (currentAct == SELECT)			
	{
		selectItem(event);
	}
	// Если действие - добавить ЛЖ, строка с текстом не пуста 
	else if (currentAct == LIFELINE)
	{
		if (localUI->nameEdit->text().length())
		{
			meta.action = LIFELINE;
			meta.name = localUI->nameEdit->text();
			meta.id = QString("LifeLine-"+localUI->nameEdit->text());
			var.setValue(meta);
			if (existDublicate(localUI->objectsList, var ))
			{	// Если нет дубликата, то добавляем
				QMessageBox::information(this, "Attention!", "This name already exists!");
				fadeInto(localUI->nameEdit, error_color);		// Отключаем раскраску поля ввода имени
				localUI->nameEdit->setFocus();
				QGraphicsView::mouseReleaseEvent(event);
			}
			else
			{
				addLifeline(mapToScene(event->x(), 30));	// Добавляем объект на сцену, задаем стандартный Y
				addToObjList(localUI->objectsList,LIFELINE, var);
			}
		}else
		{
			blink(localUI->nameEdit,normal_color, error_color,2);		    // Мигаем красным
			localUI->nameEdit->setFocus();									// Фокусируемся на строке имени
		}
	}
	else if (currentAct == COMMENT)
	{
		if (localUI->descrEdit->toPlainText().length())
		{
			meta.action = COMMENT;
			meta.name = localUI->nameEdit->text();
			meta.desc = localUI->descrEdit->toPlainText();
			meta.id = QString("Comment-"+localUI->nameEdit->text());
			var.setValue(meta);
			if (existDublicate(localUI->objectsList, var ))	// Если нет дубликата
				QMessageBox::information(this, "Attention!", "This comment already exist on scene!");
			else
				addComment(mapToScene(event->x(), event->y()));	// Добавляем объект на сцену, задаем стандартный Y
			addToObjList(localUI->objectsList,COMMENT, var);
		}
		else
		{
			blink(localUI->descrEdit,normal_color, error_color,2);		    // Мигаем красным
			localUI->descrEdit->setFocus();									// Фокусируемся на строке описания
		}
	}
	
}

/** Функция добавления линии жизни на сцену. */
void GraphWidget::addLifeline(QPointF point)
{
	Lifeline* header = new Lifeline(this);			// Создаем заголовок

	point.setY(30);							// Задаем стандартную коорлинату по У
	header->setPos(point);						// Задаем координаты
	header->name = getParentWindow()->getUI()->nameEdit->text();		// Задаем текст

	scene->addItem(header);						// Добавляем на сцену зкголовок

	this->currentAct = SELECT;					// Задаем текущее действие
	this->setCursor(Qt::ArrowCursor);			// Задаем ноовый курсор

	emit getParentWindow()->selection(true);	// Вызываем слот выбора объекта
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

/** Функция выбора объекта. */
void GraphWidget::selectItem(QMouseEvent * event)
{
	QGraphicsItem *item;
	Lifeline * line;
	FreeComment * com;

	item = scene->itemAt(event->posF(),QTransform());

	if (item!=NULL && item->type()!=6)
		this->mainWnd->getUI()->actDelete->setEnabled(true);
	else
		this->mainWnd->getUI()->actDelete->setEnabled(false);

	// Снять выделение с текущего объекта, если надо
	if (currentItem != NULL && item != currentItem)
	{
		// Если это линия жезни
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

	// Выделить новый объект, сделать его текущим
	if (item != NULL)
	{
		currentItem = item;

		// Если это линия жезни
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

/** Удаление объекта со сцены. */
void GraphWidget::removeCurrentItem()
{
	scene->removeItem(currentItem);
}

























	//if (currentItem == NULL && item != NULL)
	//{
	//	currentItem = item;

	//	line = (Lifeline*)currentItem;
	//	line->setSelected(true);
	//	line->update();
	//	line = NULL;
	//}
	//else if (item == NULL && currentItem != NULL)
	//{
	//	line = (Lifeline*)currentItem;
	//	line->setSelected(false);
	//	line->update();
	//	line = NULL;
	//}
	//else if (item != NULL && currentItem != NULL)
	//{
	//	line = (Lifeline*)currentItem;
	//	line->setSelected(false);
	//	line->update();


	//	currentItem = item;

	//	line = (Lifeline*)currentItem;
	//	line->setSelected(true);
	//	line->update();
	//	line = NULL;
	//}