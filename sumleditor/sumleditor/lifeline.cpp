#include "StdAfx.h"
#include "lifeline.h"
#include <QPen>

/** Конструктор по умолчанию. */
Lifeline::Lifeline(GraphWidget *graphWidget)
{
	graph = graphWidget;
	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	this->setCursor(Qt::SizeAllCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

/** Деструктор по умолчанию. */
Lifeline::~Lifeline()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF Lifeline::boundingRect() const
{
	return QRectF(0,0,7,300);
}

/** Вернуть форму фигуры. */
QPainterPath  Lifeline::shape() const
{
	QPainterPath path;
	path.addRect(0,0,7,300);

	return path;
}

/** Нарисовать фигуру. */
void  Lifeline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLine line (0,0,0,300);
	QPen pen = QPen(Qt::DashLine);
	pen.setWidth(2);
	pen.setDashOffset(3);
	painter->setPen(pen);
	painter->drawLine(line);
}

/** Событие клика пользователем на фигуру. */
void  Lifeline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** Задать полям координат текущие значения координат объекта на сцене. */
void Lifeline::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** Задать объекту координаты на сцене. */
void Lifeline::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}