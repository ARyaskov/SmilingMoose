#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "comfunctions.h"


class SumleditorClass;

static QList<QTreeWidgetItem* > listItems;


/** Цвет состояния "Предупреждение" */
static QColor warning_color;

/** Цвет состояния "Ошибка" */
static QColor error_color;

/** Цвет состояния "Внимание" */
static QColor attention_color;

/** Цвет состояния "Стандартное" */
static QColor normal_color;

/**
 * Перечисление состояний программы.
 */
enum Action
{	
	SELECT,		/** Выбор объекта на сцене.			  */
	
	LIFELINE,	/** Добавление линии жизни.			  */
	
	MESSAGE,	/** Добавление сообщения.			  */
	
	CREATE,		/** Добавление сообщения создания.	  */
	
	DELETE,		/** Добавление сообщения удаления.	  */
	
	REPLY,		/** Добавление возвратного сообшения. */
	
	STOP,		/** Остановка линии жизни.			  */

	COMMENT		/** Добавление комментария.			  */
};


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
    Sumleditor* getParentWindow()const { return mainWnd; }

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
	 * Добавление на сцену комментария
	 * @param point Точка, в которую поместится объект
	 */
	void addComment(QPointF point);

	/** 
	 * Выбор объекта на сцене.
	 */
	void selectItem(QMouseEvent * event);

	/** 
	 * Удаление объекта со сцены.
	 */
	void removeCurrentItem();


private:
	QGraphicsScene* scene;  /** Указатель на динамический объект сцены. */

	Action currentAct;		/** Текущее действие. */

	Sumleditor *mainWnd;	/** Указатель на главное окно. */

	QGraphicsItem *currentItem;

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
