#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_sumleditor.h"
#include "graphwidget.h"
#include "validators.h"
#include "comfunctions.h"
#include "lifeline.h"


/**
 * ������������ ���� ���������.
 */
enum MessageType
{	
	MSIMPLE,		    /** ������� ���������.          	  */
	
	MCREATE,	        /** ��������� ��������.	        	  */
	
	MDELETE,	        /** ��������� ��������.			      */
	 
	MRETURN,		    /** ��������� � ���������.	          */
	
	MFROM_SPACE,		/** ��������� "�� �������".       	  */
	
	MTO_SPACE		    /** ��������� "� ������".             */
};

class Sumleditor : public QMainWindow
{
	Q_OBJECT

public:
	Sumleditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Sumleditor();

        Ui::SumleditorClass* getUI() {return &ui;}

	/**
	 * ������� ����������� ���������� �������
	 */
	void setToolbarDefault();

	/**
	 * ������� ���������� ������� ��� �������� ���������� ����-����.
	 */
	void setToolbarAdding();

	/**
	 * ������� ������ ��������� � ���� xml ���������.
	 */
	void saveToFile ();

private:
	Ui::SumleditorClass ui;
	
	GraphWidget* diagram;	/** ����������� ������ �����. */

	QValidator * nameLE_val;/** ��������� ���� ����� �����. */

	QString filename; /** ��� ����� - �������. */

public slots:
	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void selection(bool checked);
private slots:


	/**
	 * ����, ������������� ��� ������� ������ ���������� ����� �����.
	 */
	void addLifeline();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ���������.
	 */
	void addMessage();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void addCreate();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void addDelete();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ����������� ���������.
	 */
	void addReply();

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void addStop();

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void addComment();
	
	/**
	 * ����, ������������� ��� ��������� ������ � ���� ����� �����.
	 */
	void nameLEChanged(const QString & text);
	
    /**
	 * ����, ������������� ��� ��������� ������ � ���� ����� ��������.
	 */
	void descrChanged(const QString &);

    /**
	 * ����, �������������� ������� �� Cancel, ���� ��  Esc
	 */
	void cancel();

	/**
	 * ����, �������������� ������� ������� ��� Del
	 */
	void deleteObj();

	/**
	 * ����, ������������� ��� ������� ������ "�����" � ������� ����.
	 */
	void slotExit();

	/**
	 * ����, ������������� ��� ������� ������ "� Qt" � ������� ����.
	 */
	void slotAboutQt();

	/**
	 * ����, ������������� ��� ������� ������ "�������" � ������� ����.
	 */
	void slotOpen();

	/**
	 * ����, ������������� ��� ������� ������ "���������" � ������� ����.
	 */
	void slotSave();

	/**
	 * ����, ������������� ��� ������� ������ "��������� ���..." � ������� ����.
	 */
	void slotSaveAs();

	/**
	 * ����, ������������� ��� ������� ������ "������������" � ������� ����.
	 */
	void slotAboutUs();

	/**
	 * ����, ������������� ��� ������� ������ "��������� ��� �����������" � ������� ����.
	 */
	void saveAsPicture();

};

#endif // SUMLEDITOR_H
