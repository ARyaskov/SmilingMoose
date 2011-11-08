#include "stdafx.h"
#include "volatile.h"
#include "message.h"

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
        return QRectF(0,0,length,30);
}

/** ������� ����� ������. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
        path.addRect(QRectF(0,0,length,30));

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

	//int qwe = this->pos().y();
	//qwe = sender->pos().y() + sender->endY - 20;
	//qwe = receiver->pos().y() + receiver->endY - 20;

	if (this->pos().y() > sender->pos().y() + sender->endY - 25)
		this->setY(sender->pos().y() + sender->endY - 25);

	if (this->pos().y() > receiver->pos().y() + receiver->endY - 25)
		this->setY(receiver->pos().y() + receiver->endY - 25);

	if (this->pos().y()<receiver->pos().y()+20 && messageType!=CREATE)
		this->setY(receiver->pos().y()+20);

        if (startX > endX)
            this->setX(endX);
        else
            this->setX(startX);

        if (!(messageType == CREATE && abs(startX-endX)<45))
            setLine(QLineF(startX,pos().y(),endX,pos().y()));
}

/** ��������� ����������, �� ������� ����� �������� ���������. */
void Message::calcCoordinates(QPointF click)
{
    if (messageType==MESSAGE || messageType==REPLY)
    {
        // ������������ �����
        // ��������� �������� �� �: ���������� ����������� + �������� �� ����� �������������� ��������� ��
        startX = sender->pos().x()+45;

        // �������� �������� �� �: ���������� ���������� + �������� �� ����� �������������� ��������� ��
        endX = receiver->pos().x()+45;

        length = abs(startX-endX);  // ����� - ��� ������ ������� �������
    }
    else if (messageType == CREATE || messageType == DESTROY)
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

	}
    

	int endY = click.y();

    // ������ �������� ����������
	if (endY>sender->endY)
		endY = sender->endY;

	if (endY>receiver->endY)
		endY = receiver->endY;

	if (endY<receiver->pos().y()+20 && messageType != CREATE)
            endY = receiver->pos().y()+20;

    if (startX < endX)
        this->setPos(startX,endY);
    else
        this->setPos(endX,endY);
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