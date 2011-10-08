#include "StdAfx.h"
#include "Header.h"

/** ����������� �� ���������. */
Header::Header(GraphWidget *graphWidget)
{
	graph = graphWidget;
	// ������ ��������� ������
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	this->setCursor(Qt::SizeAllCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

/** ���������� �� ���������. */
Header::~Header()
{

}

/** ������� ������������� ������ ������. */
QRectF Header::boundingRect() const
{
	return QRectF(0,0,90,30);
}

/** ������� ����� ������. */
QPainterPath  Header::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,30);

	return path;
}

/** ���������� ������. */
void  Header::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// ������ �������� ������

	gradient.setColorAt(0, QColor(Qt::yellow).dark(120));	// ����� ���������
	gradient.setColorAt(1, QColor(Qt::darkYellow).dark(100));

	// ���������� ������������� �������
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 2));
	painter->drawRect(0,0,90,30);

	QRectF textRect(5,5,80,20);								// ������������� � �������

	// ������ �����
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::black);

	// ������ �������� ������
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),graph->getParentWindow()->getUI()->nameEdit->text(),opt); // Create shadow of the name

	// ���������� �����
	painter->setPen(Qt::white);
	painter->drawText(textRect, graph->getParentWindow()->getUI()->nameEdit->text(), opt);
}

/** ������� ����� ������������� �� ������. */
void  Header::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** ������ ����� ��������� ������� �������� ��������� ������� �� �����. */
void Header::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** ������ ������� ���������� �� �����. */
void Header::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}