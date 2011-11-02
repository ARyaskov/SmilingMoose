#ifndef MESSAGE_H
#define MESSAGE_H

#include "Lifeline.h"


class Message : public QGraphicsLineItem 
{
public:

	Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver);

	/**
	 * ����������.
	 */
	~Message();

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
	 * ������� �� ������.
	 * @param ���� ���������.
	 */
	inline void setSelected(bool flag) { isSelected = flag; }
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
	enum { Type = 2 };

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

	Lifeline * sender;		/** �� �����������. */
							
	Lifeline * receiver;	/** �� ����������.  */

protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param ������� ����.
	 */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * ������� �������� ���� ��� ������� ������ ����.
	 * @param ������� ����.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

private:

	QRectF bndRect;			/** ����� �������.  */

	GraphWidget* graph;		/** ��������� �� ������, �� ������� ������. */

	double x;				/** ���������� �� ��� �. */	

	double y;				/** ���������� �� ��� y. */

	double z;				/** ���������� �� ��� Z. */

	bool isSelected;		/** ���� ��������� ������� �������. */

	int length;

public:
	
	QString name;	/** ���.	  */

	QString descr;	/** ��������. */

	QString param;	/** ��������. */
};

#endif // MESSAGE_H
