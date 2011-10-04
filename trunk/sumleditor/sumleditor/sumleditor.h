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
	void selection(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ���������� ����� �����.
	 */
	void addLifeline(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ���������� ���������.
	 */
	void addMessage(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void addCreate(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ���������� ��������� �������� ����� �����.
	 */
	void addDelete(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ���������� ����������� ���������.
	 */
	void addReply(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void addStop(bool checked);

	/**
	 * ����, ������������� ��� ������� ������ ������ �������.
	 */
	void addComment(bool checked);
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