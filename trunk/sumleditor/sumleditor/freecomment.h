#ifndef FREECOMMENT_H
#define FREECOMMENT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>

#include "graphwidget.h"

class GraphWidget;

/**
 * Класс описывающий свободный комментарий на сцене.
 */
class FreeComment : public QGraphicsItem
{
public:
	/**
	 * Конструктор по умолчанию.
	 * @param graphWidget Указатель на виджет, на котором будем рисовать.
	 */
	FreeComment(GraphWidget *graphWidget);

	/**
	 * Деструктор.
	 */
	~FreeComment();

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
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	/**
	 * Перечисление идентификатор типа объекта.
	 */
	enum { Type = 1 };

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

	/** Имя объекта. */
	QString name;

	/** Текст комментария. */
	QString text;

};

#endif // FREECOMMENT_H
