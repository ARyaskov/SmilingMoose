#ifndef LIFELINE_H
#define LIFELINE_H

#include <QGraphicsItem>
#include <QRectF>

#include <QPainterPath>
#include "graphwidget.h"
#include "sumleditor.h"

class GraphWidget;
class LifeLine;



/**
 * �����, ����������� ������ � ��� ����� �����.
 */
class LifeLine : public QGraphicsItem
{
public:
	/**
	 * ����������� �� ���������. 
	 * @param graphWidget ��������� �� ������, �� ������� ����� ��������.
	 */
	LifeLine(GraphWidget *graphWidget);

	/**
	 * ����������.
	 */
	~LifeLine();

	/** 
	 * ������� ������������� ������ ������.
	 * @return ������ ��������������.
	 */
	QRectF boundingRect() const;

	/** 
	 * ������� ����� ������.
	 * @return ������ �����.
	 */
	QPainterPath shape() const;

	/**
	 * ���������� ������.
	 * @param painter ���������� ��������.
	 * @param option �������� ���������.
	 * @param widget ������, �� ������� ������.
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	/**
	 * ������������ ������������� ���� �������.
	 */
	enum { Type = 0 };

	/**
	 * ������� ������������� ���� �������.
	 * @return ������������� ���� �������.
	 */
    inline int type() const { return Type; }

protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param ������� ����.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	/** ��������� �� ������, �� ������� ������. */
	GraphWidget		*graph;
};

#endif // LIFELINE_H
