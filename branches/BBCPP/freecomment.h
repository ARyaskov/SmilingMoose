#pragma once
#ifndef FREECOMMENT_H
#define FREECOMMENT_H


/**
 * Класс описывающий свободный комментарий на сцене.
 */
class FreeComment : public QGraphicsItem
{
public:
	/** Текст комментария. */
	QString text;

	/**
	 * Конструктор по умолчанию.
	 * @param graphWidget Указатель на виджет, на котором будем рисовать.
	 */
        FreeComment(class GraphWidget *graphWidget);

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

	/**
	 * Сохранение свободного комментария в файл.
	 * @param domDoc Главный узел, документ, файла.
	 * @return Текущий элемент узла в файле.
	 */
        QDomElement save (QDomDocument & domDoc);

	/**
	 * Считывание свободного комментария из файла.
	 * @param element Текущий узел файла.
	 */
	void load (const QDomElement & element);

	/**
	 * Функция получения координаты x.
	 * @return Координата x.
	 */
	inline double getX () { return x; }

	/**
	 * Функция получения координаты y.
	 * @return Координата y.
	 */
	inline double getY () { return y; }

	Ui::SumleditorClass* getUI();
protected:

	/** 
	 * Событие клика пользователем на фигуру.
	 * @param Событие мыши.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	/** Указатель на виджет, на котором рисуем. */
        class GraphWidget		*graph;

	/** Имя объекта. */
	QString name;
	
	double x; /** Координата по оси Х. */

	double y; /** Координата по оси y. */

	double z; /** Координата по оси Z. */

	bool isSelected;	/** Флаг выделения данного объекта. */

	/**
	 * Функция обрезания текста комментария для его корректного отображения.
	 * @return корректный текст.
	 */
	QString parseText ();
};

#endif // FREECOMMENT_H
