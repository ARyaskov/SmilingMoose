#include "stdafx.h"
#include "volatile.h"
#include "message.h"
#include <QGraphicsSceneMouseEvent>

enum Action;

/** Конструктор по умолчанию. */
Message::Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver, QPointF click, enum Action messageType)
{
	graph = graphWidget;
	sender = _sender;
	receiver = _receiver;
	this->messageType = messageType;

	// Задаем параметры фигуре
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);

	this->setCursor(Qt::PointingHandCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(1);

	isSelected = false;
	hasReply = false;

	this->x = 0;
	this->y = 0;
	this->z = 0;

	parentMsg = (Message*)graphWidget->getCurrentItem();

	calcCoordinates(click);
}

/** Деструктор по умолчанию. */
Message::~Message()
{

}

/** Вернуть прямоугольник границ фигуры. */
QRectF Message::boundingRect() const
{
        return QRectF(-10,0,length+20,35);
}

/** Вернуть форму фигуры. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
        path.addRect(QRectF(-10,0,length+20,35));

	return path;
}

/** Нарисовать фигуру. */
void  Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;			// Задаем стиль рисования
    pen.setWidth(2);	// Задаем в стиле толщину линии

	if (messageType == REPLY)
		pen.setStyle(Qt::DashLine);

    if (isSelected)
        pen.setColor(Qt::red);
    else
        pen.setColor(Qt::black);

    // Область линии - прямоугольник размером length * 20
    QLine line (length,25,0,25);	// Создаем линию заданной длины с координатой по У 15,
                                                                    // а в простренстве от 0 до 15 над ней будет текст
    painter->setPen(pen);			// Задаем отрисовщику стиль
    painter->drawLine(line);		// Рисуем линию

    if ( (startX < endX && messageType != REPLY) || (startX > endX && messageType == REPLY))	// Если координата конца левее координаты начала
    {
            // Рисуем линию с права на лево
            painter->drawLine(length-10,20,length,25);
            painter->drawLine(length-10,30,length,25);
    }
    else				// Если координата конца правее координаты начала
    {
            // Рисуем линию с лева на право
            painter->drawLine(0,25,10,20);
            painter->drawLine(0,25,10,30);
    }

    // Добавить текстовое поле с именем сообщения над стрелкой
    QRectF textRect(5,8,length-10,18);   // Прямоугольник с текстом в поле по У от 0 до 10, и по Х от 5 до длина-5

    // Задать шрифт
    QFont font = painter->font();
    font.setBold(true);				// Стиль "жирный"
    font.setPointSize(10);			// Размер шрифта

    painter->setFont(font);			// Задаем шрифт
    painter->setPen(pen);		// Задаем  цвет

    // Задать свойства тексту
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);		// Выравнивание по центру

	if (messageType == REPLY)
		painter->drawText(textRect,QString("Re: ") + name,opt);	// Рисуем текст
	else
		painter->drawText(textRect,name,opt);	// Рисуем текст

	if (messageType==CREATE)
	{
		textRect.setRect(5,0,length-10,10);

		font.setBold(false);				// Стиль "жирный"
		font.setPointSize(8);			// Размер шрифта

		painter->setFont(font);			// Задаем шрифт
		painter->drawText(textRect,QString("<<create>>"),opt);
	}

	if (messageType==DESTROY)
	{
		textRect.setRect(5,0,length-10,10);

		font.setBold(false);				// Стиль "жирный"
		font.setPointSize(8);			// Размер шрифта

		painter->setFont(font);			// Задаем шрифт
		painter->drawText(textRect,QString("<<destroy>>"),opt);

		if ( startX < endX )
		{
			painter->drawLine(length-10,15,length+10,35);
			painter->drawLine(length-10,35,length+10,15);
		}
		else
		{
			painter->drawLine(-10,15,10,35);
			painter->drawLine(-10,35,10,15);
		}
	}
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
	if (messageType!=CREATE)
		QGraphicsItem::mouseMoveEvent(event);

	// Устанавливаем координату по Х, чтобы не вылезало слева
    if (startX > endX)
        this->setX(endX);
    else
        this->setX(startX);

	// Чтобы не вылезало за пределы СЕНДЕРА снизу
	if (pos().y() > sender->pos().y() + sender->endY - 25)
		setY(sender->pos().y() + sender->endY - 25);

	// Чтобы не вылезало за пределы РЕСИВЕРА снизу
	if (pos().y() > receiver->pos().y() + receiver->endY - 25)
		setY(receiver->pos().y() + receiver->endY - 25);
 
	// Чтобы не вылезало выше сообщения создания
	if (pos().y() < receiver->pos().y()+20 && messageType!=CREATE)
		this->setY(receiver->pos().y()+20);

	// Если получатель не налезает на создающую его ЛЖ - проводим линию данной длины
	if (!(messageType == CREATE && abs(startX-endX)<45))
		setLine(QLineF(startX,pos().y(),endX,pos().y()));

	// Чтобы нельзя было поднять ЛЖ выше самого нижнего сообщения
	int buf = this->pos().y();

	// Если это сообщение нижнее записать ее координату

	if (isLowestMessage(sender,receiver,buf))
	{
		sender->lastMessageCoord = buf;
		receiver->lastMessageCoord = buf;
	}

	if (messageType==DESTROY)
	{
		this->receiver->lastMessageCoord = buf-1;
		this->receiver->setSize(buf);
	}
}

/** Вычислить координату, из которой будет исходить сообщение. */
void Message::calcCoordinates(QPointF click)
{
    if (messageType==MESSAGE || messageType==REPLY || messageType == DESTROY)
    {
        // Рассчитываем длину
        // Стартовая пощзиция по Х: координата отправителя + половина от длины прямоугольника заголовка ЛЖ
        startX = sender->pos().x()+45;

        // Конечная пощзиция по Х: координата получателя + половина от длины прямоугольника заголовка ЛЖ
        endX = receiver->pos().x()+45;

        length = abs(startX-endX);  // Длина - это модуль разницы позиций
    }
    else if (messageType == CREATE)
    {
        // Рассчитываем длину
        startX = sender->pos().x()+45;
        endX = receiver->pos().x();

        if (sender->pos().x()+45>=receiver->pos().x()+90)
        {
            startX = sender->pos().x()+45;
            endX = receiver->pos().x()+90;
        }

        length = abs(startX-endX);  // Длина - это модуль разницы позиций

        if (receiver->pos().x()<=sender->pos().x()+45 && receiver->pos().x()>=sender->pos().x()-45)
            length=0;
	}

	if (messageType == CREATE)
	{
        receiver->setY(click.y());
	}
	else if (messageType == DESTROY)
	{
		receiver->setSize(click.y());
	}
    
	int currEndY = click.y();

	// Задаем диапазон координате сообщения создания
	if (currEndY < receiver->pos().y()+20 && messageType != CREATE)
		currEndY = receiver->pos().y()+20;

    if (startX < endX)
        this->setPos(startX,currEndY);
    else
        this->setPos(endX,currEndY);
}

bool Message::isTopMessage(Lifeline *snd, Lifeline *rec, QPointF click)
{
	QListIterator<Message*>i(snd->messages);
	bool result = true;
	Message *buf;

	while(i.hasNext() && result)
	{
		buf = i.next();
		if (buf->receiver == rec && buf->pos().y() <= click.y())
			result = false;
	}

	return result;
}

bool Message::hasUpperCreate(Lifeline *snd, Lifeline *rec, QPointF click)
{
	QListIterator<Message*>i(rec->messages);
	bool result = true;
	Message *buf;

	while(i.hasNext() && result)
	{
		buf = i.next();
		if (buf->messageType == CREATE && buf->pos().y() <= click.y())
			result = false;
	}

	return result;
}

bool Message::isLowestMessage(Lifeline *snd, Lifeline *rec, int curY)
{
	QListIterator<Message*>i(snd->messages);
	bool result = true;
	Message *buf;

	while(i.hasNext() && result)
	{
		buf = i.next();
		if (buf->receiver == rec && buf->pos().y() > curY)
			result = false;
	}

	return result;
}

bool Message::hasLowerDestr(Lifeline *snd, Lifeline *rec, QPointF click)
{
	QListIterator<Message*>i(rec->messages);
	bool result = true;
	Message *buf;

	while(i.hasNext() && result)
	{
		buf = i.next();
		if (buf->messageType == DESTROY && buf->pos().y() > click.y())
			result = false;
	}

	return result;
}


	//{
	//	if (buf <=sender->endY)
	//		sender->lastMessageCoord = buf;
	//	else
	//		sender->lastMessageCoord = sender->endY;

	//	if (buf <=receiver->endY)
	//		receiver->lastMessageCoord = buf;
	//	else
	//		receiver->lastMessageCoord = receiver->endY;
	//}