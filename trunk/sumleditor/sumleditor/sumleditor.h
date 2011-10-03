#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_sumleditor.h"
#include "graphwidget.h"
#include "freecomment.h"

class sumleditor : public QMainWindow
{
	Q_OBJECT

public:
	sumleditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~sumleditor();

private:
	Ui::sumleditorClass ui;

	/** Графический виджет сцены. */
	GraphWidget* diagram;

private slots:
	/** 
	 * Слот для добавления комментария на сцену. 
	 * @param isChecked Нажата ли кнопка.
	 */
	void addComment(bool isChecked);

	/** 
	 * Слот для задания текста комментарию.
	 */
	void setComment();
};

#endif // SUMLEDITOR_H
