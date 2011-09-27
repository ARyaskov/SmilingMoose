#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

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
	QGraphicsScene* scene;
	
};

#endif // GRAPHWIDGET_H
