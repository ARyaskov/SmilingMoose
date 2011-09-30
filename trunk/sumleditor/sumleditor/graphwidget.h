#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "lifeline.h"
#include "freecomment.h"

class LifeLine;
class FreeComment;

/**
 * �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����.
 */
class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	/**
	 * ����������� �� ���������.
	 * @param parent ��������� �� ����, � ������ ��������� ������.
	 */
	GraphWidget(QWidget *parent = 0);

	/**
	 * �����������.
	 */
	~GraphWidget();

private:
	/** ��������� �� ������������ ������ �����. */
	QGraphicsScene* scene;

protected:
	/** 
	 * ������� ��������� �������� ����.
	 * @param event ��������� �� ������� �������.
	 */
	void wheelEvent(QWheelEvent *event);

	/** 
	 * ������� ��������������� �����.
	 * @param scaleFactor �������� ���������.
	 */
	void scaleView(qreal scaleFactor);

private slots:
	/** 
	 * �������� ���� ���������� ������� �� �����.
	 * @param isChecked ������ �� ������.
	 */
	void addObject(bool isChecked);

	/**
	 * ���� ���������� ����������� �� �����.
	 * @param isChecked ������ �� ������.
	 */
	void addComment(bool isChecked);
};

#endif // GRAPHWIDGET_H
