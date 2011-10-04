#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "lifeline.h"
#include "freecomment.h"

class Sumleditor;
class LifeLine;
class FreeComment;

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

/**
 * Класс, реализующий виджет сцены для отрисовки диаграммы в главном окне.
 */
class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	/**
	 * Конструктор по умолчанию.
	 * @param parent Указатель на окно, в отором создается виджет.
	 */
	GraphWidget(QWidget *parent = 0);

	/**
	 * Десктруктор.
	 */
	~GraphWidget();

private:
	QGraphicsScene* scene;  /** Указатель на динамический объект сцены. */

	Action currentAct;		/** Текущее действие. */

	Sumleditor *mainWnd;	/** Указатель на главное окно. */

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

private slots:

};

#endif // GRAPHWIDGET_H









	///** Последний созданный объект. */
	//QGraphicsItem *lastItem;

	/** 
	 * ТЕСТОВЫЙ слот добавления объекта на сцену.
	 * @param isChecked Нажата ли кнопка.
	 */
	//void addObject(bool isChecked);



	/**
	 * Слот добавления комментария на сцену.
	 * @param isChecked Нажата ли кнопка.
	 */
	//void addComment();
