#pragma once
#ifndef LIFELINE_H
#define LIFELINE_H


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

        /**
	* Функция сохранения линии жизни в файл.
	* @param domDoc Главный узел, документ, файла.
	* @param id Идентификатор линий жизни, для организации хранения сообщений.
	* @return Текущий элемент узла в файле.
        */
        QDomElement save (QDomDocument & domDoc, int id);

        /**
         * Функция считывания линии жизни из файла.
         * @param element Узел дерева в файле.
         */
        void load (const QDomElement & element);

	/**
	 * Изменить текущее состояние завершенности Л.Ж.
	 */
	inline void setEnded() { isEnd = !isEnd; }

        /**
         * Получение состояния: имеет ли линия жизни конец.
         * @return имеет ли линия жизни конец.
         */
        inline bool isEnded() { return isEnd; }

	/**
	 * Идентификатор линии жизни,
	 * используется при сохранении/считывани файла.
	 */
	int id;

	inline void setSelectedByMessage(bool flag) { isSelectedByMessage = flag; }

        /**
         * Получение координаты x.
         * @return Значение координаты x.
         */
        inline double getX() { return x; }

        /**
         * Получение координаты y.
         * @return Значение координаты y.
         */
        inline double getY() { return y; }

        /**
         * Получение координаты z.
         * @return Значение координаты z.
         */
        inline double getZ() { return z; }

        QList<class Message*>messages;	/** Контейнер, сообщений данной ЛЖ. */

        inline Ui::SumleditorClass* getUI(){
	        return this->graph->getParentWindow()->getUI();
        };
		
		int lastMessageCoord;

		int endY;

		void setSize(int newY);

		inline void setName(const QString& newName) {name = newName;};

		bool isDestroyed;           /** Флаг, означающий, что данная Л.Ж. остановлена другой Л.Ж. */

		bool isEnd;                 /** Флаг, наличия конца линии жизни. */
protected:

	/** 
	 * Событие клика пользователем на фигуру.
	 * @param event Событие мыши.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/** 
	 * Событие движения мыши при зажатой кнопке мыши.
	 * @param event Событие мыши.
	 */
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

	
	/** 
	 * Событие двойного щелчка мыши.
	 * @param event Событие мыши.
	 */
	void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );

private:
	/** Указатель на виджет, на котором рисуем. */
	GraphWidget		*graph;

	double x;                   /** Координата по оси Х. */

	double y;                   /** Координата по оси y. */

	double z;                   /** Координата по оси Z. */

	bool isSelected;            /** Флаг выделения данного объекта. */

	bool isSelectedByMessage;   /** Флаг, означающий, что данная Л.Ж. выделена при добавлении сообщения. */



	bool isCreated;             /** Флаг, означающий, что данная Л.Ж. порождена другой Л.Ж. */

	QRectF bndRect;

};

#endif // LIFELINE_H
