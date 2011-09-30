#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "lifeline.h"
#include "freecomment.h"

class LifeLine;
class FreeComment;

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
	/** Указатель на динамический объект сцены. */
	QGraphicsScene* scene;

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
	/** 
	 * ТЕСТОВЫЙ слот добавления объекта на сцену.
	 * @param isChecked Нажата ли кнопка.
	 */
	void addObject(bool isChecked);

	/**
	 * Слот добавления комментария на сцену.
	 * @param isChecked Нажата ли кнопка.
	 */
	void addComment(bool isChecked);
};

#endif // GRAPHWIDGET_H
