#include "stdafx.h"
#include "volatile.h"
#include "message.h"
#include <QGraphicsSceneMouseEvent>

enum Action;

/** ����������� �� ���������. */
Message::Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver, QPointF click, enum Action messageType)
{
	graph = graphWidget;
	sender = _sender;
	receiver = _receiver;
	this->messageType = messageType;

	// ������ ��������� ������
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

/** ���������� �� ���������. */
Message::~Message()
{

}

/** ������� ������������� ������ ������. */
QRectF Message::boundingRect() const
{
        return QRectF(-10,0,length+20,35);
}

/** ������� ����� ������. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
        path.addRect(QRectF(-10,0,length+20,35));

	return path;
}

/** ���������� ������. */
void  Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;			// ������ ����� ���������
    pen.setWidth(2);	// ������ � ����� ������� �����

	if (messageType == REPLY)
		pen.setStyle(Qt::DashLine);

    if (isSelected)
        pen.setColor(Qt::red);
    else
        pen.setColor(Qt::black);

    // ������� ����� - ������������� �������� length * 20
    QLine line (length,25,0,25);	// ������� ����� �������� ����� � ����������� �� � 15,
                                                                    // � � ������������ �� 0 �� 15 ��� ��� ����� �����
    painter->setPen(pen);			// ������ ����������� �����
    painter->drawLine(line);		// ������ �����

    if ( (startX < endX && messageType != REPLY) || (startX > endX && messageType == REPLY))	// ���� ���������� ����� ����� ���������� ������
    {
            // ������ ����� � ����� �� ����
            painter->drawLine(length-10,20,length,25);
            painter->drawLine(length-10,30,length,25);
    }
    else				// ���� ���������� ����� ������ ���������� ������
    {
            // ������ ����� � ���� �� �����
            painter->drawLine(0,25,10,20);
            painter->drawLine(0,25,10,30);
    }

    // �������� ��������� ���� � ������ ��������� ��� ��������
    QRectF textRect(5,8,length-10,18);   // ������������� � ������� � ���� �� � �� 0 �� 10, � �� � �� 5 �� �����-5

    // ������ �����
    QFont font = painter->font();
    font.setBold(true);				// ����� "������"
    font.setPointSize(10);			// ������ ������

    painter->setFont(font);			// ������ �����
    painter->setPen(pen);		// ������  ����

    // ������ �������� ������
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);		// ������������ �� ������

	if (messageType == REPLY)
		painter->drawText(textRect,QString("Re: ") + name,opt);	// ������ �����
	else
		painter->drawText(textRect,name,opt);	// ������ �����

	if (messageType==CREATE)
	{
		textRect.setRect(5,0,length-10,10);

		font.setBold(false);				// ����� "������"
		font.setPointSize(8);			// ������ ������

		painter->setFont(font);			// ������ �����
		painter->drawText(textRect,QString("<<create>>"),opt);
	}

	if (messageType==DESTROY)
	{
		textRect.setRect(5,0,length-10,10);

		font.setBold(false);				// ����� "������"
		font.setPointSize(8);			// ������ ������

		painter->setFont(font);			// ������ �����
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
	if (messageType!=CREATE)
		QGraphicsItem::mouseMoveEvent(event);

	// ������������� ���������� �� �, ����� �� �������� �����
    if (startX > endX)
        this->setX(endX);
    else
        this->setX(startX);

	// ����� �� �������� �� ������� ������� �����
	if (pos().y() > sender->pos().y() + sender->endY - 25)
		setY(sender->pos().y() + sender->endY - 25);

	// ����� �� �������� �� ������� �������� �����
	if (pos().y() > receiver->pos().y() + receiver->endY - 25)
		setY(receiver->pos().y() + receiver->endY - 25);
 
	// ����� �� �������� ���� ��������� ��������
	if (pos().y() < receiver->pos().y()+20 && messageType!=CREATE)
		this->setY(receiver->pos().y()+20);

	// ���� ���������� �� �������� �� ��������� ��� �� - �������� ����� ������ �����
	if (!(messageType == CREATE && abs(startX-endX)<45))
		setLine(QLineF(startX,pos().y(),endX,pos().y()));

	// ����� ������ ���� ������� �� ���� ������ ������� ���������
	int buf = this->pos().y();

	// ���� ��� ��������� ������ �������� �� ����������

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

/** ��������� ����������, �� ������� ����� �������� ���������. */
void Message::calcCoordinates(QPointF click)
{
    if (messageType==MESSAGE || messageType==REPLY || messageType == DESTROY)
    {
        // ������������ �����
        // ��������� �������� �� �: ���������� ����������� + �������� �� ����� �������������� ��������� ��
        startX = sender->pos().x()+45;

        // �������� �������� �� �: ���������� ���������� + �������� �� ����� �������������� ��������� ��
        endX = receiver->pos().x()+45;

        length = abs(startX-endX);  // ����� - ��� ������ ������� �������
    }
    else if (messageType == CREATE)
    {
        // ������������ �����
        startX = sender->pos().x()+45;
        endX = receiver->pos().x();

        if (sender->pos().x()+45>=receiver->pos().x()+90)
        {
            startX = sender->pos().x()+45;
            endX = receiver->pos().x()+90;
        }

        length = abs(startX-endX);  // ����� - ��� ������ ������� �������

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

	// ������ �������� ���������� ��������� ��������
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