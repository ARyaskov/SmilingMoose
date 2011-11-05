#include "stdafx.h"
#include "message.h"

enum Action;

/** Конструктор по умолчанию. */
Message::Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver, enum Action messageType)
{
	graph = graphWidget;
	sender = _sender;
	receiver = _receiver;

	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);

	this->setCursor(Qt::PointingHandCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(1);

	isSelected = false;

	this->x = NULL;
	this->y = NULL;
	this->z = NULL;

	int startX = receiver->pos().x()+45;
	
	int endX = sender->pos().x()+45;
		
	length = abs(startX-endX);

	bndRect = QRectF(0,0,length,10);
}

/** Деструктор по умолчанию. */
Message::~Message()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF Message::boundingRect() const
{
        return QRectF(0,0,length,20);
}

/** Вернуть форму фигуры. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
        path.addRect(QRectF(0,0,length,20));

	return path;
}

/** Нарисовать фигуру. */
void  Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen;
	pen.setWidth(2);

        QLine line (length,15,0,15);
	painter->setPen(pen);
	painter->drawLine(line);

	int startX = receiver->pos().x()+45;
	int endX = sender->pos().x()+45;

        length = abs(startX-endX);

	if (endX < startX)
	{
                painter->drawLine(length-10,10,length,15);
                painter->drawLine(length-10,20,length,15);
	}
	else
	{
                painter->drawLine(0,15,10,10);
                painter->drawLine(0,15,10,20);
	}

        // Добавить текстовое поле с именем сообщения над стрелкой
        QRectF textRect(5,0,length-5,10);   // Прямоугольник с текстом

        // Задать шрифт
        QFont font = painter->font();
        font.setBold(true);
        font.setPointSize(10);

        painter->setFont(font);
        painter->setPen(Qt::black);

        // Задать свойства тексту
        QTextOption opt;
        opt.setAlignment(Qt::AlignCenter);

        painter->drawText(textRect,name,opt);
}

/** Событие клика пользователем на фигуру. */
void  Message::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** Задать полям координат текущие значения координат объекта на сцене. */
void Message::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** Задать объекту координаты на сцене. */
void Message::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}

/** Событие движения мыши при зажатой кнопке мыши. */
void Message::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	QGraphicsItem::mouseMoveEvent(event);

	int startX = sender->pos().x()+45;

	int endX = receiver->pos().x()+45;

	if (startX > endX)
		startX = endX;

	if (this->pos().y()>300)
		this->setY(300);

	if (this->pos().y()<60)
		this->setY(60);

	this->setX(startX);
	setLine(QLineF(startX,pos().y(),endX,pos().y()));
}

/** Вычислить координату, из которой будет исходить сообщение. */
void Message::calcMessCoords(QPointF snd, QPointF rcv, QPointF click)
{
        int retX, retY;
        // Вычисляем координату Y

        retY = click.y();

        // Задаем диапазон координате
        if (retY>300)
                retY = 300;

        if (retY<60)
                retY = 100;

        // Определяем стартовую координту по Х
        retX = snd.x()+45;

        int endX = rcv.x()+45;

        if (retX > endX)
                retX = rcv.x()+45;

        this->setPos(retX,retY);
}
