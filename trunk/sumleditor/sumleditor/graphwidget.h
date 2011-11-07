
#pragma once
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H




struct ElementMetaInfo
{
  Action action;
  QString name;
  QString desc;
  QString id;
  QHash<QString, QGraphicsItem*> array;
};



 Q_DECLARE_METATYPE(ElementMetaInfo)
/**
 * Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне.
 */
class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	inline QGraphicsScene *getScene() { return scene; }
	/**
	 * Конструктор по умолчанию.
	 * @param parent Указатель на окно, в отором создается виджет.
	 */
	GraphWidget(QWidget *parent = 0);

	/**
	 * Десктруктор.
	 */
	~GraphWidget();

    /** 
	 * Функция возвращает указатель на объект пользовательского интерфейса
	 */
    class Sumleditor* getParentWindow() { return mainWnd; }

	/** 
	 * Вернуть текущее действие.
	 * @return Текущее действие.
	 */
	Action getCurrentAct()const { return this->currentAct; }

	/** 
	 * Функция проверяет есть ли на сцене линия жизни с таким же именем
	 * @param newAct Новое действие.
	 */
	void setCurrentAct(Action newAct) { this->currentAct = newAct; }

	/** 
	 * Добавление на сцену линии жизни
	 * @param point Точка, в которую поместится объект
	 */
	void addLifeline(QPointF point);

        /**
         * Добавление на сцену линии жизни
         * @param lifeline Указатель на добовляемую линию жизни.
         */
        void addLifeline(class Lifeline* lifeline);

	/** 
	 * Подготовка добавления новой ЛЖ
	 * @param event указатель на текущее событие нажатия мыши
	 */
	void initNewLifeline(QMouseEvent * event);

	/** 
	 * Подготовка добавления нового комментария
	 * @param point Точка, в которую поместится объект
	 */
	void initNewComment(QPointF point);

	/** 
	 * Подготовка добавления нового сообщения
	 * @param event указатель на текущее событие нажатия мыши
	 */
	void initNewMessage(QMouseEvent * event);

	/** 
	 * Добавление на сцену комментария
	 * @param point Точка, в которую поместится объект
	 */
	void addComment(QPointF point);

        /**
         * Добавление на сцену комментария
         * @param commet Указатель на добовляемый комментарий
         */
        void addComment(FreeComment *commet);

	/**
	 * Добавление сообщения между линиями жизни.
	 * @param point Точка, в которую поместится объект
	 */ 
	void addMessage(QPointF point);

	/**
	 * Остановка линии жизни.
	 * @param point Точка, в которую поместится объект
	 */ 
	void addStop(QPointF point);

	/** 
	 * Выбор объекта на сцене.
	 */
	void selectItem(QPointF point);

	/** 
	 * Удаление объекта со сцены.
	 */
	void removeCurrentItem();
	
	/**
	 * Функция сохранения диаграммы в файл.
	 * @param domDoc Главный узел, документ, файла.
	 * @return Текущий элемент узла в файле.
	 */
	QDomElement save(QDomDocument & domDoc);

        /**
         * Функция считывания диаграммы из файла.
         * @param node Узел дерева из файла.
         */
        void load(const QDomNode & node);

	/**
	 * Функция сохранения свойств диаграммы в файл.
	 * @param domDoc Главный узел, документ файла.
	 * @return Текущий элемент узла в файле.
	 */
	QDomElement saveProperties (QDomDocument & domDoc);

	/** 
	 * Получить текущий элемент сцены.
	 */
        inline QGraphicsItem *getCurrentItem() { return currentItem; }

	/**
	 * Добавить на сцену ось на заданном уровне.
	 */
	void addAxis(int level);



private:
	QGraphicsScene* scene;  /** Указатель на динамический объект сцены. */

	Action currentAct;		/** Текущее действие. */

	Sumleditor *mainWnd;	/** Указатель на главное окно. */

	QGraphicsItem *currentItem;

	Lifeline * sendLine;

	Lifeline * recLine;

protected:
	/** 
	 * Событие прокрутки колесика мыши.
	 * @param event Указатель на текущее событие.
	 */
	void wheelEvent(QWheelEvent *event);

	/** 
	 * Функция масштабирования сцены.
	 * @param scaleFactor Величина прокрутки.
	 */
	void scaleView(qreal scaleFactor);
	
	/** 
	 * Событие перемещения указателя мыши
	 * @param event Указатель на событие.
	 */
    //void mouseMoveEvent ( QMouseEvent * event );

	/** 
	 * Событие нажатия на кнопку мыши
	 * @param event Указатель на событие.
	 */
    void mousePressEvent(QMouseEvent * event);

private slots:
	/** 
	 * Слот, реагирующий на изменения сцены
	 */
	void sceneChanged();

};

#endif // GRAPHWIDGET_H
