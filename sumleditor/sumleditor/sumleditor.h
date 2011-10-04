#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_sumleditor.h"
#include "graphwidget.h"
#include "freecomment.h"

class Sumleditor : public QMainWindow
{
	Q_OBJECT

public:
	Sumleditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Sumleditor();

private:
	Ui::SumleditorClass ui;
	
	GraphWidget* diagram;	/** ����������� ������ �����. */

private slots:
	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void selection();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ����� �����.
	 */
	void setLifelineAdding();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ���������.
	 */
	void setMessageAdding();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void setCreateAdding();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void setDeleteAdding();

	/**
	 * ����, ������������� ��� ������� ������ ���������� ����������� ���������.
	 */
	void setReplyAdding();

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void setStopAdding();

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void setCommentAdding();
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
	//void setComment();