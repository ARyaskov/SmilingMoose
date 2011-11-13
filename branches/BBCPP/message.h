#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H


class Message : public QGraphicsLineItem 
{
public:

        Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver, QPointF click, enum Action messageType = MESSAGE);

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


    /** ��������� ����������, �� ������� ����� �������� ���������. */
	void calcCoordinates(QPointF click);

	static bool isTopMessage(Lifeline *snd, Lifeline *rec, QPointF click);

	static bool hasUpperCreate(Lifeline *snd, Lifeline *rec, QPointF click);

	static bool isLowestMessage(Lifeline *snd, Lifeline *rec, int curY);

	static bool hasLowerDestr(Lifeline *snd, Lifeline *rec, QPointF click);

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

        GraphWidget* graph; /** ��������� �� ������, �� ������� ������. */

        double x;           /** ���������� �� ��� �. */

        double y;           /** ���������� �� ��� y. */

        double z;           /** ���������� �� ��� Z. */

        bool isSelected;    /** ���� ��������� ������� �������. */

        int length;         /** ����� ������� ���������. */

        int startX;

        int endX;

public:
	
	QString name;	/** ���.	  */

	QString descr;	/** ��������. */

	QString param;	/** ��������. */

	bool hasReply;  /** ����, ����������, ��� � ������� ���������. ��� ���� �����. */

	enum Action messageType;        /** ��� ���������. */

	Message* parentMsg;
};

#endif // MESSAGE_H
