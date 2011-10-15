#include "StdAfx.h"
#include "freecomment.h"

/** Конструктор по умолчанию. */
FreeComment::FreeComment(GraphWidget *graphWidget)
{
	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(2);
	isSelected = false;
	this->setCursor(Qt::PointingHandCursor);
}

/** Деструктор по умолчанию. */
FreeComment::~FreeComment()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF FreeComment::boundingRect() const
{
	return QRectF(0,0,100,50);
}

/** Вернуть форму фигуры. */
QPainterPath  FreeComment::shape() const
{
	QPainterPath path;
	path.addRect(0,0,100,50);

	return path;
}

/** Нарисовать фигуру. */
void  FreeComment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,100,50);					// Задать градиент фигуре

	if (isSelected)
	{
		gradient.setColorAt(0, QColor(Qt::yellow).light(150));	// Цвета градиента
		gradient.setColorAt(1, QColor(Qt::darkYellow).light(150));
	}
	else
	{
		gradient.setColorAt(0, QColor(Qt::yellow));	// Цвета градиента
		gradient.setColorAt(1, QColor(Qt::darkYellow));
	}

	QPen pen;
	pen.setWidth(2);

	// Нарисовать прямоугольник объекта
	painter->setBrush(gradient);

	if (isSelected)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::black);

	painter->setPen(pen);
	painter->drawRect(0,0,100,50);
	
	QRectF textRect(5,5,90,40);								// Прямоугольник с текстом

	// Задать шрифт
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	///painter->setPen(Qt::black);

	// Задать свойства тексту
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	//painter->drawText(textRect.translated(2, 2),text,opt); // Create shadow of the name
	
	// Нарисовать текст
	painter->setPen(Qt::black);
	painter->drawText(textRect,text, opt);
}

/** Событие клика пользователем на фигуру. */
void  FreeComment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** Задать полям координат текущие значения координат объекта на сцене. */
void FreeComment::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** Задать объекту координаты на сцене. */
void FreeComment::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}