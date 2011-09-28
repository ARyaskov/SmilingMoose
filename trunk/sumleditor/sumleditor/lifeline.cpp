#include "StdAfx.h"
#include "lifeline.h"

/** Конструктор по умолчанию. */
LifeLine::LifeLine(GraphWidget *graphWidget)
{
	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

/** Деструктор по умолчанию. */
LifeLine::~LifeLine()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF LifeLine::boundingRect() const
{
	return QRectF(0,0,90,90);
}

/** Вернуть форму фигуры. */
QPainterPath  LifeLine::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,90);

	return path;
}

/** Нарисовать фигуру. */
void  LifeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// Задать градиент фигуре

	gradient.setColorAt(0, QColor(Qt::cyan).light(100));	// Цвета градиента
	gradient.setColorAt(1, QColor(Qt::darkCyan));

	// Нарисовать прямоугольник объекта
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 2));
	painter->drawRect(0,0,90,30);
	
	QRectF textRect(0,0,90,30);								// Прямоугольник с текстом

	// Задать шрифт
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::black);

	// Задать свойства тексту
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),QString("LifeLine 1"),opt); // Create shadow of the name
	
	// Нарисовать текст
	painter->setPen(Qt::white);
	painter->drawText(textRect, QString("LifeLine 1"), opt);

	// Нарисовать линию
	QPen test(Qt::black,1,Qt::DashLine);
	painter->setPen(test);
	painter->drawLine(45,30,45,90);
}

/** Событие клика пользователем на фигуру. */
void  LifeLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}