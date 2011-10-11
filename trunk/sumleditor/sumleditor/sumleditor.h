#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "validators.h"
#include "comfunctions.h"
#include "objlist.h"
#include "ui_sumleditor.h"


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

	Ui::SumleditorClass* getUI() {return &ui;};

	/**
	 * ������� ����������� ���������� �������
	 */
	void setToolbarDefault();

	/**
	 * ������� ���������� ������� ��� �������� ����������.
	 */
	void setToolbarAdding();

private:
	Ui::SumleditorClass ui;
	
	GraphWidget* diagram;	/** ����������� ������ �����. */

	QValidator * nameLE_val;/** ��������� ���� ����� �����. */

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
	 * ����, ������������� ��� ��������� ������ � ���� �����.
	 */
	void nameLEChanged(const QString & text);
	
    /**
	 * ����, �������������� ������� �� Cancel, ���� ��  Esc
	 */
	void cancel();

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





















	///** 
	// * ���� ��� ���������� ����������� �� �����. 
	// * @param isChecked ������ �� ������.
	// */
	//void addComment(bool isChecked);

	///** 
	// * ���� ��� ������� ������ �����������.
	// */
	//void addComment();