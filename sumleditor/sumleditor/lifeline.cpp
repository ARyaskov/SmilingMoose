#include "StdAfx.h"
#include "Lifeline.h"

/** Конструктор по умолчанию. */
Lifeline::Lifeline(GraphWidget *graphWidget)
{
	graph = graphWidget;
	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	this->setCursor(Qt::PointingHandCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(1);
	isSelected = false;
}

/** Деструктор по умолчанию. */
Lifeline::~Lifeline()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF Lifeline::boundingRect() const
{
	return QRectF(0,0,90,300);
}

/** Вернуть форму фигуры. */
QPainterPath  Lifeline::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,300);

	return path;
}

/** Нарисовать фигуру. */
void  Lifeline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// Задать градиент фигуре

	if (isSelected)
	{
		gradient.setColorAt(0, QColor(Qt::yellow).light(100));	// Цвета градиента
		gradient.setColorAt(1, QColor(Qt::darkYellow).light(100));
	}
	else
	{
		gradient.setColorAt(0, QColor(Qt::yellow).dark(100));	// Цвета градиента
		gradient.setColorAt(1, QColor(Qt::darkYellow).dark(100));
	}
	// Нарисовать прямоугольник объекта
	painter->setBrush(gradient);

	QPen pen;
	pen.setWidth(2);

	if (isSelected)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::black);

	painter->setPen(pen);
	painter->drawRect(0,0,90,30);

	QRectF textRect(5,5,80,20);								// Прямоугольник с текстом

	// Задать шрифт
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::black);

	// Задать свойства тексту
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),name,opt); 
	// Нарисовать текст
	painter->setPen(Qt::white);
	painter->drawText(textRect, name, opt);

	QLine line (45,30,45,300);
	pen.setStyle(Qt::DashLine);
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

/** Событие движения мыши при зажатой кнопке мыши. */
void Lifeline::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	QGraphicsItem::mouseMoveEvent(event);
	this->setY(30);							// Линия жизни остается на одной координате У
}