#include "StdAfx.h"
#include "lifeline.h"

/** ����������� �� ���������. */
LifeLine::LifeLine(GraphWidget *graphWidget)
{
	// ������ ��������� ������
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

/** ���������� �� ���������. */
LifeLine::~LifeLine()
{

}

/** ������� ������������� ������ ������. */
QRectF LifeLine::boundingRect() const
{
	return QRectF(0,0,90,90);
}

/** ������� ����� ������. */
QPainterPath  LifeLine::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,90);

	return path;
}

/** ���������� ������. */
void  LifeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// ������ �������� ������

	gradient.setColorAt(0, QColor(Qt::cyan).light(100));	// ����� ���������
	gradient.setColorAt(1, QColor(Qt::darkCyan));

	// ���������� ������������� �������
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 2));
	painter->drawRect(0,0,90,30);
	
	QRectF textRect(0,0,90,30);								// ������������� � �������

	// ������ �����
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::black);

	// ������ �������� ������
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),QString("LifeLine 1"),opt); // Create shadow of the name
	
	// ���������� �����
	painter->setPen(Qt::white);
	painter->drawText(textRect, QString("LifeLine 1"), opt);

	// ���������� �����
	QPen test(Qt::black,1,Qt::DashLine);
	painter->setPen(test);
	painter->drawLine(45,30,45,90);
}

/** ������� ����� ������������� �� ������. */
void  LifeLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}