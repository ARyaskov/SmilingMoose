#ifndef FREECOMMENT_H
#define FREECOMMENT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include "comfunctions.h"



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

	/**
	 * ������ ����� ��������� ������� �������� ��������� ������� �� �����.
	 */
	void getCurrentCoords();

	/**
	 * ������ ������� ���������� �� �����.
	 * @param newX ���������� �� X.
	 * @param newY ���������� �� Y.
	 * @param newZ ���������� �� Z.
	 */
	void setCoords(double newX, double newY, double newZ);

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
	
	double x; /** ���������� �� ��� �. */

	double y; /** ���������� �� ��� y. */

	double z; /** ���������� �� ��� Z. */
};

#endif // FREECOMMENT_H
