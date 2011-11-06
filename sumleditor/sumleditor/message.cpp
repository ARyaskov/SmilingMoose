#include "stdafx.h"
#include "message.h"

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

        this->x = 0;
        this->y = 0;
        this->z = 0;

        calcCoordinates(click);
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
	QPen pen;			// Задаем стиль рисования
	pen.setWidth(2);	// Задаем в стиле толщину линии

	// Область линии - прямоугольник размером length * 20
        QLine line (length,15,0,15);	// Создаем линию заданной длины с координатой по У 15,
									// а в простренстве от 0 до 15 над ней будет текст
	painter->setPen(pen);			// Задаем отрисовщику стиль
	painter->drawLine(line);		// Рисуем линию

	if (endX < startX)	// Если координата конца левее координаты начала
	{
		// Рисуем линию с права на лево
		painter->drawLine(length-10,10,length,15);
		painter->drawLine(length-10,20,length,15);
	}
	else				// Если координата конца правее координаты начала
	{
		// Рисуем линию с лева на право
		painter->drawLine(0,15,10,10);
		painter->drawLine(0,15,10,20);
	}

    // Добавить текстовое поле с именем сообщения над стрелкой
    QRectF textRect(5,0,length-5,10);   // Прямоугольник с текстом в поле по У от 0 до 10, и по Х от 5 до длина-5

    // Задать шрифт
    QFont font = painter->font();
    font.setBold(true);				// Стиль "жирный"
    font.setPointSize(10);			// Размер шрифта

    painter->setFont(font);			// Задаем шрифт
    painter->setPen(Qt::black);		// Задаем  цвет

    // Задать свойства тексту
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);		// Выравнивание по центру

    painter->drawText(textRect,name,opt);	// Рисуем текст
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
void Message::calcCoordinates(QPointF click)
{
    if (messageType==MESSAGE)
    {
        // Рассчитываем длину
        // Стартовая пощзиция по Х: координата отправителя + половина от длины прямоугольника заголовка ЛЖ
        startX = receiver->pos().x()+45;

        // Конечная пощзиция по Х: координата получателя + половина от длины прямоугольника заголовка ЛЖ
        endX = sender->pos().x()+45;
    }
    else if (messageType == CREATE)
    {

    }
    else
    {

    }

    length = abs(startX-endX);  // Длина - это модуль разницы позиций

    int endY = click.y();

    // Задаем диапазон координате
    if (endY>300)
            endY = 300;

    if (endY<60)
            endY = 100;

    if (startX < endX)
        this->setPos(startX,endY);
    else
        this->setPos(endX,endY);
}
