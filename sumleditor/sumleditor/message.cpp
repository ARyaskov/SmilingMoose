#include "stdafx.h"
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

	// ������� ����� - ������������� �������� length * 20
        QLine line (length,15,0,15);	// ������� ����� �������� ����� � ����������� �� � 15,
									// � � ������������ �� 0 �� 15 ��� ��� ����� �����
	painter->setPen(pen);			// ������ ����������� �����
	painter->drawLine(line);		// ������ �����

	if (endX < startX)	// ���� ���������� ����� ����� ���������� ������
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
    painter->setPen(Qt::black);		// ������  ����

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
void Message::calcCoordinates(QPointF click)
{
    if (messageType==MESSAGE)
    {
        // ������������ �����
        // ��������� �������� �� �: ���������� ����������� + �������� �� ����� �������������� ��������� ��
        startX = receiver->pos().x()+45;

        // �������� �������� �� �: ���������� ���������� + �������� �� ����� �������������� ��������� ��
        endX = sender->pos().x()+45;
    }
    else if (messageType == CREATE)
    {

    }
    else
    {

    }

    length = abs(startX-endX);  // ����� - ��� ������ ������� �������

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
