#include "StdAfx.h"
#include "freecomment.h"

/** ����������� �� ���������. */
FreeComment::FreeComment(GraphWidget *graphWidget)
{
	// ������ ��������� ������
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(2);
	isSelected = false;
	this->setCursor(Qt::PointingHandCursor);
}

/** ���������� �� ���������. */
FreeComment::~FreeComment()
{

}

/** ������� ������������� ������ ������. */
QRectF FreeComment::boundingRect() const
{
	return QRectF(0,0,100,50);
}

/** ������� ����� ������. */
QPainterPath  FreeComment::shape() const
{
	QPainterPath path;
	path.addRect(0,0,100,50);

	return path;
}

/** ���������� ������. */
void  FreeComment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,100,50);					// ������ �������� ������

	if (isSelected)
	{
		gradient.setColorAt(0, QColor(Qt::yellow).light(150));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkYellow).light(150));
	}
	else
	{
		gradient.setColorAt(0, QColor(Qt::yellow));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkYellow));
	}

	QPen pen;
	pen.setWidth(2);

	// ���������� ������������� �������
	painter->setBrush(gradient);

	if (isSelected)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::black);

	painter->setPen(pen);
	painter->drawRect(0,0,100,50);
	
	QRectF textRect(5,5,90,40);								// ������������� � �������

	// ������ �����
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	///painter->setPen(Qt::black);

	// ������ �������� ������
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	//painter->drawText(textRect.translated(2, 2),text,opt); // Create shadow of the name
	
	// ���������� �����
	painter->setPen(Qt::black);
	painter->drawText(textRect,text, opt);
}

/** ������� ����� ������������� �� ������. */
void  FreeComment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** ������ ����� ��������� ������� �������� ��������� ������� �� �����. */
void FreeComment::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** ������ ������� ���������� �� �����. */
void FreeComment::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}