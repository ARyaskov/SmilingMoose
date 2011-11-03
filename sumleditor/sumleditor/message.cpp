#include "stdafx.h"
#include "message.h"

/** ����������� �� ���������. */
Message::Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver)
{
	graph = graphWidget;
	sender = _sender;
	receiver = _receiver;

	// ������ ��������� ������
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

/** ���������� �� ���������. */
Message::~Message()
{

}

/** ������� ������������� ������ ������. */
QRectF Message::boundingRect() const
{
	return QRectF(0,0,length,10);
}

/** ������� ����� ������. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
	path.addRect(QRectF(0,0,length,10));

	return path;
}

/** ���������� ������. */
void  Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen;
	pen.setWidth(2);

	QLine line (length,5,0,5);
	painter->setPen(pen);
	painter->drawLine(line);

	int startX = receiver->pos().x()+45;
	int endX = sender->pos().x()+45;

        length = abs(startX-endX);

	if (endX < startX)
	{
		painter->drawLine(length-10,0,length,5);
		painter->drawLine(length-10,10,length,5);
	}
	else
	{
		painter->drawLine(0,5,10,0);
		painter->drawLine(0,5,10,10);
	}
	
}

/** ������� ����� ������������� �� ������. */
void  Message::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** ������ ����� ��������� ������� �������� ��������� ������� �� �����. */
void Message::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** ������ ������� ���������� �� �����. */
void Message::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}

/** ������� �������� ���� ��� ������� ������ ����. */
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

/** ��������� ����������, �� ������� ����� �������� ���������. */
void Message::calcMessCoords(QPointF snd, QPointF rcv, QPointF click)
{
        int retX, retY;
        // ��������� ���������� Y

        retY = click.y();

        // ������ �������� ����������
        if (retY>300)
                retY = 300;

        if (retY<60)
                retY = 100;

        // ���������� ��������� ��������� �� �
        retX = snd.x()+45;

        int endX = rcv.x()+45;

        if (retX > endX)
                retX = rcv.x()+45;

        this->setPos(retX,retY);
}
