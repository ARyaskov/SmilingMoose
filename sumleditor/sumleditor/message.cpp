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

        this->x = 0;
        this->y = 0;
        this->z = 0;

        calcCoordinates(click);
}

/** ���������� �� ���������. */
Message::~Message()
{

}

/** ������� ������������� ������ ������. */
QRectF Message::boundingRect() const
{
        return QRectF(0,0,length,20);
}

/** ������� ����� ������. */
QPainterPath  Message::shape() const
{
	QPainterPath path;
        path.addRect(QRectF(0,0,length,20));

	return path;
}

/** ���������� ������. */
void  Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;			// ������ ����� ���������
    pen.setWidth(2);	// ������ � ����� ������� �����

    if (isSelected)
        pen.setColor(Qt::red);
    else
        pen.setColor(Qt::black);

    // ������� ����� - ������������� �������� length * 20
    QLine line (length,15,0,15);	// ������� ����� �������� ����� � ����������� �� � 15,
                                                                    // � � ������������ �� 0 �� 15 ��� ��� ����� �����
    painter->setPen(pen);			// ������ ����������� �����
    painter->drawLine(line);		// ������ �����

    if (startX < endX)	// ���� ���������� ����� ����� ���������� ������
    {
            // ������ ����� � ����� �� ����
            painter->drawLine(length-10,10,length,15);
            painter->drawLine(length-10,20,length,15);
    }
    else				// ���� ���������� ����� ������ ���������� ������
    {
            // ������ ����� � ���� �� �����
            painter->drawLine(0,15,10,10);
            painter->drawLine(0,15,10,20);
    }

    // �������� ��������� ���� � ������ ��������� ��� ��������
    QRectF textRect(5,0,length-5,10);   // ������������� � ������� � ���� �� � �� 0 �� 10, � �� � �� 5 �� �����-5

    // ������ �����
    QFont font = painter->font();
    font.setBold(true);				// ����� "������"
    font.setPointSize(10);			// ������ ������

    painter->setFont(font);			// ������ �����
    painter->setPen(pen);		// ������  ����

    // ������ �������� ������
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);		// ������������ �� ������

    painter->drawText(textRect,name,opt);	// ������ �����
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

	if (this->pos().y()>300)
		this->setY(300);

	if (this->pos().y()<60)
		this->setY(60);

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
    if (messageType==MESSAGE)
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



        receiver->setY(click.y());
    }
    else
    {

    }



    int endY = click.y();

    // ������ �������� ����������
    if (endY>300)
            endY = 300;

    if (endY<60)
            endY = 100;

    if (startX < endX)
        this->setPos(startX,endY);
    else
        this->setPos(endX,endY);
}
