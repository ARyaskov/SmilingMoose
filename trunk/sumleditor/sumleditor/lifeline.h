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
 * Класс, описывающий объект и его линию жизни.
 */
class LifeLine : public QGraphicsItem
{
public:
	/**
	 * Конструктор по умолчанию. 
	 * @param graphWidget Указатель на виджет, на котором будем рисовать.
	 */
	LifeLine(GraphWidget *graphWidget);

	/**
	 * Деструктор.
	 */
	~LifeLine();

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
	 * Нарисовать фигуру.
	 * @param painter Отрисовщик объектов.
	 * @param option Свойства отрисовки.
	 * @param widget Виджет, на котором рисуем.
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	/**
	 * Перечисление идентификатор типа объекта.
	 */
	enum { Type = 0 };

	/**
	 * Вернуть идентификатор типа объекта.
	 * @return Идентификатор типа объекта.
	 */
    inline int type() const { return Type; }

protected:

	/** 
	 * Событие клика пользователем на фигуру.
	 * @param Событие мыши.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	/** Указатель на виджет, на котором рисуем. */
	GraphWidget		*graph;
};

#endif // LIFELINE_H
