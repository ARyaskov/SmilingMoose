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
	void selection();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления линии жизни.
	 */
	void setLifelineAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения.
	 */
	void setMessageAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
	 */
	void setCreateAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
	 */
	void setDeleteAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
	 */
	void setReplyAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void setStopAdding();

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void setCommentAdding();
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
	//void setComment();