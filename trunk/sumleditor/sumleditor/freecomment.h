#ifndef FREECOMMENT_H
#define FREECOMMENT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>

#include "graphwidget.h"

class GraphWidget;

/**
 * ����� ����������� ��������� ����������� �� �����.
 */
class FreeComment : public QGraphicsItem
{
public:
	/** ����� �����������. */
	QString text;

	/**
	 * ����������� �� ���������.
	 * @param graphWidget ��������� �� ������, �� ������� ����� ��������.
	 */
	FreeComment(GraphWidget *graphWidget);

	/**
	 * ����������.
	 */
	~FreeComment();

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
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	/**
	 * ������������ ������������� ���� �������.
	 */
	enum { Type = 1 };

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

	/** ��� �������. */
	QString name;
};

#endif // FREECOMMENT_H
