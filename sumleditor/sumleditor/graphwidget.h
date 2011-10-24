#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "comfunctions.h"


class SumleditorClass;

static QList<QTreeWidgetItem* > listItems;


/** ���� ��������� "��������������" */
static QColor warning_color;

/** ���� ��������� "������" */
static QColor error_color;

/** ���� ��������� "��������" */
static QColor attention_color;

/** ���� ��������� "�����������" */
static QColor normal_color;

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
 * �����, ����������� ������ ����� ��� ��������� ��������� � ������� ����.
 */
class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	inline QGraphicsScene *getScene() { return scene; }
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
	 * ������� ������� ��������.
	 * @return ������� ��������.
	 */
	Action getCurrentAct()const { return this->currentAct; }

	/** 
	 * ������� ��������� ���� �� �� ����� ����� ����� � ����� �� ������
	 * @param newAct ����� ��������.
	 */
	void setCurrentAct(Action newAct) { this->currentAct = newAct; }

	/** 
	 * ���������� �� ����� ����� �����
	 * @param point �����, � ������� ���������� ������
	 */
	void addLifeline(QPointF point);

	/** 
	 * ���������� �� ����� �����������
	 * @param point �����, � ������� ���������� ������
	 */
	void addComment(QPointF point);

	/** 
	 * ����� ������� �� �����.
	 */
	void selectItem(QMouseEvent * event);

	/** 
	 * �������� ������� �� �����.
	 */
	void removeCurrentItem();


private:
	QGraphicsScene* scene;  /** ��������� �� ������������ ������ �����. */

	Action currentAct;		/** ������� ��������. */

	Sumleditor *mainWnd;	/** ��������� �� ������� ����. */

	QGraphicsItem *currentItem;

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
    //void mouseMoveEvent ( QMouseEvent * event );

	/** 
	 * ������� ������� �� ������ ����
	 * @param event ��������� �� �������.
	 */
    void mousePressEvent(QMouseEvent * event);

private slots:
	/** 
	 * ����, ����������� �� ��������� �����
	 */
	void sceneChanged();

};

#endif // GRAPHWIDGET_H
