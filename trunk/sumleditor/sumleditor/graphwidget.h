#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "comfunctions.h"
#include "lifeline.h"
#include "freecomment.h"

class Sumleditor;



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

    /** 
	 * ������� ���������� ��������� �� ������ ����������������� ����������
	 */
    Sumleditor* getParentWindow()const { return mainWnd; }

	/** 
	 * ������� ��������� ���� �� �� ����� ����� ����� � ����� �� ������
	 */
	bool existDublicate();
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

	
	/** 
	 * ������� ����������� ��������� ����
	 * @param event ��������� �� �������.
	 */
    void mouseMoveEvent ( QMouseEvent * event );

	/** 
	 * ������� ������� �� ������ ����
	 * @param event ��������� �� �������.
	 */
    void mousePressEvent(QMouseEvent * event);

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
