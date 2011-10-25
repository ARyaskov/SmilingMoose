#ifndef LIFELINE_H
#define LIFELINE_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include <QDomDocument>
#include "comfunctions.h"


/**
 * �����, ����������� ������ � ��� ����� �����.
 */
class Lifeline : public QGraphicsItem
{
public:

	QString name;	/** ��� ���������. */

	/**
	 * ����������� �� ���������. 
	 * @param graphWidget ��������� �� ������, �� ������� ����� ��������.
	 */
	Lifeline(GraphWidget *graphWidget);

	/**
	 * ����������.
	 */
	~Lifeline();

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
	inline void setSelected(bool flag){ isSelected = flag; }

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

	/************************************************************************
	* ������� ���������� ����� ����� � ����.
	* @param domDoc ������� ����, ��������, �����.
	* @param id ������������� ����� �����, ��� ����������� �������� ���������.
	* @return ������� ������� ���� � �����.
	************************************************************************/
	QDomElement save (QDomDocument & domDoc, int id) const;

	/**
	 * �������� ������� ��������� ������������� �.�.
	 */
	inline void setEnded() { isEnd = !isEnd; }

	inline void setSelectedByMessage(bool flag) { isSelectedByMessage = flag; }

protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param ������� ����.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * ������� �������� ���� ��� ������� ������ ����.
	 * @param ������� ����.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

private:
	/** ��������� �� ������, �� ������� ������. */
	GraphWidget		*graph;

	double x; /** ���������� �� ��� �. */

	double y; /** ���������� �� ��� y. */

	double z; /** ���������� �� ��� Z. */

	bool isSelected;	/** ���� ��������� ������� �������. */

	bool isSelectedByMessage;

	bool isEnd; /** ����, ������� ����� ����� �����. */
};

#endif // LIFELINE_H
