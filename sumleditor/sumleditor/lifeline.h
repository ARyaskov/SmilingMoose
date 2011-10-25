#ifndef LIFELINE_H
#define LIFELINE_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include <QDomDocument>
#include "comfunctions.h"


/**
 * Класс, описывающий объект и его линию жизни.
 */
class Lifeline : public QGraphicsItem
{
public:

	QString name;	/** Имя заголовка. */

	/**
	 * Конструктор по умолчанию. 
	 * @param graphWidget Указатель на виджет, на котором будем рисовать.
	 */
	Lifeline(GraphWidget *graphWidget);

	/**
	 * Деструктор.
	 */
	~Lifeline();

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
	inline void setSelected(bool flag){ isSelected = flag; }

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

	/************************************************************************
	* Функция сохранения линии жизни в файл.
	* @param domDoc Главный узел, документ, файла.
	* @param id Идентификатор линий жизни, для организации хранения сообщений.
	* @return Текущий элемент узла в файле.
	************************************************************************/
	QDomElement save (QDomDocument & domDoc, int id) const;

	/**
	 * Изменить текущее состояние завершенности Л.Ж.
	 */
	inline void setEnded() { isEnd = !isEnd; }

	inline void setSelectedByMessage(bool flag) { isSelectedByMessage = flag; }

protected:

	/** 
	 * Событие клика пользователем на фигуру.
	 * @param Событие мыши.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * Событие движения мыши при зажатой кнопке мыши.
	 * @param Событие мыши.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

private:
	/** Указатель на виджет, на котором рисуем. */
	GraphWidget		*graph;

	double x; /** Координата по оси Х. */

	double y; /** Координата по оси y. */

	double z; /** Координата по оси Z. */

	bool isSelected;	/** Флаг выделения данного объекта. */

	bool isSelectedByMessage;

	bool isEnd; /** Флаг, наличия конца линии жизни. */
};

#endif // LIFELINE_H
