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
	
	GraphWidget* diagram;	/** Графический виджет сцены. */

private slots:
	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void selection(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления линии жизни.
	 */
	void addLifeline(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения.
	 */
	void addMessage(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
	 */
	void addCreate(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
	 */
	void addDelete(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
	 */
	void addReply(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void addStop(bool checked);

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void addComment(bool checked);
};

#endif // SUMLEDITOR_H





















	///** 
	// * Слот для добавления комментария на сцену. 
	// * @param isChecked Нажата ли кнопка.
	// */
	//void addComment(bool isChecked);

	///** 
	// * Слот для задания текста комментарию.
	// */
	//void addComment();