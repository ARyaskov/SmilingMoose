#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "lifeline.h"
#include "freecomment.h"

class Sumleditor;
class LifeLine;
class FreeComment;

/**
 * ������������ ��������� ���������.
 */
enum Action
{	
	SELECT,		/** ����� ������� �� �����.			  */
	
	LIFELINE,	/** ���������� ����� �����.			  */
	
	MESSAGE,	/** ���������� ���������.			  */
	
	CREATE,		/** ���������� ��������� ��������.	  */
	
	DELETE,		/** ���������� ��������� ��������.	  */
	
	REPLY,		/** ���������� ����������� ���������. */
	
	STOP,		/** ��������� ����� �����.			  */

	COMMENT		/** ���������� �����������.			  */
};

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
	QGraphicsScene* scene;  /** ��������� �� ������������ ������ �����. */

	Action currentAct;		/** ������� ��������. */

	Sumleditor *mainWnd;	/** ��������� �� ������� ����. */

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

};

#endif // GRAPHWIDGET_H









	///** ��������� ��������� ������. */
	//QGraphicsItem *lastItem;

	/** 
	 * �������� ���� ���������� ������� �� �����.
	 * @param isChecked ������ �� ������.
	 */
	//void addObject(bool isChecked);



	/**
	 * ���� ���������� ����������� �� �����.
	 * @param isChecked ������ �� ������.
	 */
	//void addComment();
