#include "StdAfx.h"
#include "Header.h"

/** Конструктор по умолчанию. */
Header::Header(GraphWidget *graphWidget)
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
Header::~Header()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF Header::boundingRect() const
{
	return QRectF(0,0,90,30);
}

/** Вернуть форму фигуры. */
QPainterPath  Header::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,30);

	return path;
}

/** Нарисовать фигуру. */
void  Header::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// Задать градиент фигуре

	gradient.setColorAt(0, QColor(Qt::yellow).dark(120));	// Цвета градиента
	gradient.setColorAt(1, QColor(Qt::darkYellow).dark(100));

	// Нарисовать прямоугольник объекта
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 2));
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

	painter->drawText(textRect.translated(2, 2),graph->getParentWindow()->getUI()->nameEdit->text(),opt); // Create shadow of the name

	// Нарисовать текст
	painter->setPen(Qt::white);
	painter->drawText(textRect, graph->getParentWindow()->getUI()->nameEdit->text(), opt);
}

/** Событие клика пользователем на фигуру. */
void  Header::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** Задать полям координат текущие значения координат объекта на сцене. */
void Header::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** Задать объекту координаты на сцене. */
void Header::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}