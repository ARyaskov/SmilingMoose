#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#include <QtGui/QMainWindow>
#include "validators.h"
#include "comfunctions.h"
#include "ui_sumleditor.h"


/**
 * Перечисление Типы сообщений.
 */
enum MessageType
{	
	MSIMPLE,		    /** Простое сообщение.          	  */
	
	MCREATE,	        /** Сообщение создания.	        	  */
	
	MDELETE,	        /** Сообщение удаления.			      */
	 
	MRETURN,		    /** Сообщение с возвратом.	          */
	
	MFROM_SPACE,		/** Сообщение "Из космоса".       	  */
	
	MTO_SPACE		    /** Сообщение "В космос".             */
};

class Sumleditor : public QMainWindow
{
	Q_OBJECT

public:
	Sumleditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Sumleditor();

	Ui::SumleditorClass* getUI() {return &ui;};
private:
	Ui::SumleditorClass ui;
	
	GraphWidget* diagram;	/** Графический виджет сцены. */

	QValidator * nameLE_val;/** Валидатор поля ввода имени. */

public slots:
	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void selection(bool checked);
private slots:


	/**
	 * Слот, срабатывающий при нажатии кнопки добавления линии жизни.
	 */
	void addLifeline();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения.
	 */
	void addMessage();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения создания линии жизни.
	 */
	void addCreate();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления сообщения удаления линии жизни.
	 */
	void addDelete();

	/**
	 * Слот, срабатывающий при нажатии кнопки добавления возвратного сообщения.
	 */
	void addReply();

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void addStop();

	/**
	 * Слот, срабатывающий при нажатии кнопки выбора объекта.
	 */
	void addComment();
	
	/**
	 * Слот, срабатывающий при изменении текста в поле ввода.
	 */
	void nameLEChanged(const QString & text);
	
    /**
	 * Слот, обрабатывающий нажатие на Cancel, либо на  Esc
	 */
	void cancel();

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