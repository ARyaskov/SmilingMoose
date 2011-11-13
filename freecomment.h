#pragma once
#ifndef FREECOMMENT_H
#define FREECOMMENT_H


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
        FreeComment(class GraphWidget *graphWidget);

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

	/**
	 * ���������� ���������� ����������� � ����.
	 * @param domDoc ������� ����, ��������, �����.
	 * @return ������� ������� ���� � �����.
	 */
        QDomElement save (QDomDocument & domDoc);

	/**
	 * ���������� ���������� ����������� �� �����.
	 * @param element ������� ���� �����.
	 */
	void load (const QDomElement & element);

	/**
	 * ������� ��������� ���������� x.
	 * @return ���������� x.
	 */
	inline double getX () { return x; }

	/**
	 * ������� ��������� ���������� y.
	 * @return ���������� y.
	 */
	inline double getY () { return y; }

	Ui::SumleditorClass* getUI();
protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param ������� ����.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	/** ��������� �� ������, �� ������� ������. */
        class GraphWidget		*graph;

	/** ��� �������. */
	QString name;
	
	double x; /** ���������� �� ��� �. */

	double y; /** ���������� �� ��� y. */

	double z; /** ���������� �� ��� Z. */

	bool isSelected;	/** ���� ��������� ������� �������. */

	/**
	 * ������� ��������� ������ ����������� ��� ��� ����������� �����������.
	 * @return ���������� �����.
	 */
	QString parseText ();
};

#endif // FREECOMMENT_H
