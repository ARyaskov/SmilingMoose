#ifndef MESSAGE_H
#define MESSAGE_H

#include "Lifeline.h"


class Message : public QGraphicsLineItem 
{
public:

	Message(GraphWidget *graphWidget, Lifeline * _sender, Lifeline * _receiver);

	/**
	 * Деструктор.
	 */
	~Message();

	/** 
	 * Вернуть прямоугольник границ фигуры.
	 * @return Объект прямоугольника.
	 */
	QRectF boundingRect() const;

	/** 
	 * Вернуть форму фигуры.
	 * @return Объект формы.
	 */
	QPainterPath shape() const;

	/**
	 * Выделен ли объект.
	 * @param Флаг выделения.
	 */
	inline void setSelected(bool flag) { isSelected = flag; }
	/**
	 * Нарисовать фигуру.
	 * @param painter Отрисовщик объектов.
	 * @param option Свойства отрисовки.
	 * @param widget Виджет, на котором рисуем.
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	/**
	 * Перечисление идентификатор типа объекта.
	 */
	enum { Type = 2 };

	/**
	 * Вернуть идентификатор типа объекта.
	 * @return Идентификатор типа объекта.
	 */
    inline int type() const { return Type; }

	/**
	 * Задать полям координат текущие значения координат объекта на сцене.
	 */
	void getCurrentCoords();

	/**
	 * Задать объекту координаты на сцене.
	 * @param newX Координата по X.
	 * @param newY Координата по Y.
	 * @param newZ Координата по Z.
	 */
	void setCoords(double newX, double newY, double newZ);

	Lifeline * sender;		/** ЛЖ отправитель. */
							
	Lifeline * receiver;	/** ЛЖ получатель.  */

protected:

	/** 
	 * Событие клика пользователем на фигуру.
	 * @param Событие мыши.
	 */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * Событие движения мыши при зажатой кнопке мыши.
	 * @param Событие мыши.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

private:

	QRectF bndRect;			/** Форма объекта.  */

	GraphWidget* graph;		/** Указатель на виджет, на котором рисуем. */

	double x;				/** Координата по оси Х. */	

	double y;				/** Координата по оси y. */

	double z;				/** Координата по оси Z. */

	bool isSelected;		/** Флаг выделения данного объекта. */

	int length;

public:
	
	QString name;	/** Имя.	  */

	QString descr;	/** Описание. */

	QString param;	/** Параметр. */
};

#endif // MESSAGE_H
