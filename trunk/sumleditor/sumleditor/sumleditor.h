#pragma once
#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4251)

#include "ui_sumleditor.h"

#pragma warning(pop)

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

        /**
         * ������� ���������� ��������� �� xml �����.
         */
        void readFromFile ();

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

	/**
	 * ����, ������������� ��� ����� ����������� �������� � ������ ��������.
	 */
	void objListCurRowChanged(int currentrow);

};

#endif // SUMLEDITOR_H
