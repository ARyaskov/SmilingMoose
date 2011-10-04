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
	setZValue(-1);
	this->setCursor(Qt::SizeAllCursor);
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

	gradient.setColorAt(0, QColor(Qt::red).light(200));	// Цвета градиента
	gradient.setColorAt(1, QColor(Qt::red).light(100));

	// Нарисовать прямоугольник объекта
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 2));
	painter->drawRect(0,0,100,50);
	
	QRectF textRect(5,5,90,40);								// Прямоугольник с текстом

	// Задать шрифт
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::darkRed);

	// Задать свойства тексту
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),text,opt); // Create shadow of the name
	
	// Нарисовать текст
	painter->setPen(Qt::white);
	painter->drawText(textRect,text, opt);
}

/** Событие клика пользователем на фигуру. */
void  FreeComment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}