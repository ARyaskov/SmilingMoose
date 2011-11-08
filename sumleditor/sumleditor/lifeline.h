#pragma once
#ifndef LIFELINE_H
#define LIFELINE_H


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

        /**
	* ������� ���������� ����� ����� � ����.
	* @param domDoc ������� ����, ��������, �����.
	* @param id ������������� ����� �����, ��� ����������� �������� ���������.
	* @return ������� ������� ���� � �����.
        */
        QDomElement save (QDomDocument & domDoc, int id);

        /**
         * ������� ���������� ����� ����� �� �����.
         * @param element ���� ������ � �����.
         */
        void load (const QDomElement & element);

	/**
	 * �������� ������� ��������� ������������� �.�.
	 */
	inline void setEnded() { isEnd = !isEnd; }

        /**
         * ��������� ���������: ����� �� ����� ����� �����.
         * @return ����� �� ����� ����� �����.
         */
        inline bool isEnded() { return isEnd; }

	/**
	 * ������������� ����� �����,
	 * ������������ ��� ����������/��������� �����.
	 */
	int id;

	inline void setSelectedByMessage(bool flag) { isSelectedByMessage = flag; }

        /**
         * ��������� ���������� x.
         * @return �������� ���������� x.
         */
        inline double getX() { return x; }

        /**
         * ��������� ���������� y.
         * @return �������� ���������� y.
         */
        inline double getY() { return y; }

        /**
         * ��������� ���������� z.
         * @return �������� ���������� z.
         */
        inline double getZ() { return z; }

        QList<class Message*>messages;	/** ���������, ��������� ������ ��. */

        inline Ui::SumleditorClass* getUI(){
	        return this->graph->getParentWindow()->getUI();
        };
		
		int lastMessageCoord;

		int endY;

		void setSize(int newY);

		inline void setName(const QString& newName) {name = newName;};

		bool isDestroyed;           /** ����, ����������, ��� ������ �.�. ����������� ������ �.�. */

		bool isEnd;                 /** ����, ������� ����� ����� �����. */
protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param event ������� ����.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * ������� �������� ���� ��� ������� ������ ����.
	 * @param event ������� ����.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

	
	/** 
	 * ������� �������� ������ ����.
	 * @param event ������� ����.
	 */
	void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );

private:
	/** ��������� �� ������, �� ������� ������. */
	GraphWidget		*graph;

	double x;                   /** ���������� �� ��� �. */

	double y;                   /** ���������� �� ��� y. */

	double z;                   /** ���������� �� ��� Z. */

	bool isSelected;            /** ���� ��������� ������� �������. */

	bool isSelectedByMessage;   /** ����, ����������, ��� ������ �.�. �������� ��� ���������� ���������. */



	bool isCreated;             /** ����, ����������, ��� ������ �.�. ��������� ������ �.�. */

	QRectF bndRect;

};

#endif // LIFELINE_H
