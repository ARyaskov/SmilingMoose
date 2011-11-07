
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
    class Sumleditor* getParentWindow() { return mainWnd; }

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
         * ���������� �� ����� ����� �����
         * @param lifeline ��������� �� ����������� ����� �����.
         */
        void addLifeline(class Lifeline* lifeline);

	/** 
	 * ���������� ���������� ����� ��
	 * @param event ��������� �� ������� ������� ������� ����
	 */
	void initNewLifeline(QMouseEvent * event);

	/** 
	 * ���������� ���������� ������ �����������
	 * @param point �����, � ������� ���������� ������
	 */
	void initNewComment(QPointF point);

	/** 
	 * ���������� ���������� ������ ���������
	 * @param event ��������� �� ������� ������� ������� ����
	 */
	void initNewMessage(QMouseEvent * event);

	/** 
	 * ���������� �� ����� �����������
	 * @param point �����, � ������� ���������� ������
	 */
	void addComment(QPointF point);

        /**
         * ���������� �� ����� �����������
         * @param commet ��������� �� ����������� �����������
         */
        void addComment(FreeComment *commet);

	/**
	 * ���������� ��������� ����� ������� �����.
	 * @param point �����, � ������� ���������� ������
	 */ 
	void addMessage(QPointF point);

	/**
	 * ��������� ����� �����.
	 * @param point �����, � ������� ���������� ������
	 */ 
	void addStop(QPointF point);

	/** 
	 * ����� ������� �� �����.
	 */
	void selectItem(QPointF point);

	/** 
	 * �������� ������� �� �����.
	 */
	void removeCurrentItem();
	
	/**
	 * ������� ���������� ��������� � ����.
	 * @param domDoc ������� ����, ��������, �����.
	 * @return ������� ������� ���� � �����.
	 */
	QDomElement save(QDomDocument & domDoc);

        /**
         * ������� ���������� ��������� �� �����.
         * @param node ���� ������ �� �����.
         */
        void load(const QDomNode & node);

	/**
	 * ������� ���������� ������� ��������� � ����.
	 * @param domDoc ������� ����, �������� �����.
	 * @return ������� ������� ���� � �����.
	 */
	QDomElement saveProperties (QDomDocument & domDoc);

	/** 
	 * �������� ������� ������� �����.
	 */
        inline QGraphicsItem *getCurrentItem() { return currentItem; }

	/**
	 * �������� �� ����� ��� �� �������� ������.
	 */
	void addAxis(int level);



private:
	QGraphicsScene* scene;  /** ��������� �� ������������ ������ �����. */

	Action currentAct;		/** ������� ��������. */

	Sumleditor *mainWnd;	/** ��������� �� ������� ����. */

	QGraphicsItem *currentItem;

	Lifeline * sendLine;

	Lifeline * recLine;

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
