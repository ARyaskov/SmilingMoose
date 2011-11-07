#pragma once
#ifndef SUMLEDITOR_H
#define SUMLEDITOR_H

#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4251)

#include "ui_sumleditor.h"

#pragma warning(pop)

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

        Ui::SumleditorClass* getUI() {return &ui;}

	/**
	 * Задание стандартных параметров тулбара
	 */
	void setToolbarDefault();

	/**
	 * Задание параметров тулбара для процесса добавления чего-либо.
	 */
	void setToolbarAdding();

	/**
	 * Функция записи диаграммы в файл xml структуры.
	 */
	void saveToFile ();

        /**
         * Функция считывания диаграммы из xml файла.
         */
        void readFromFile ();

private:
	Ui::SumleditorClass ui;
	
	GraphWidget* diagram;	/** Графический виджет сцены. */

	QValidator * nameLE_val;/** Валидатор поля ввода имени. */

	QString filename; /** Имя файла - проекта. */

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
	 * Слот, срабатывающий при изменении текста в поле ввода имени.
	 */
	void nameLEChanged(const QString & text);
	
    /**
	 * Слот, срабатывающий при изменении текста в поле ввода описания.
	 */
	void descrChanged(const QString &);

    /**
	 * Слот, обрабатывающий нажатие на Cancel, либо на  Esc
	 */
	void cancel();

	/**
	 * Слот, обрабатывающий нажатие удалить или Del
	 */
	void deleteObj();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Выход" в главном меню.
	 */
	void slotExit();

	/**
	 * Слот, срабатывающий при нажатии кнопки "О Qt" в главном меню.
	 */
	void slotAboutQt();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Открыть" в главном меню.
	 */
	void slotOpen();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Сохранить" в главном меню.
	 */
	void slotSave();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Сохранить как..." в главном меню.
	 */
	void slotSaveAs();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Разработчики" в главном меню.
	 */
	void slotAboutUs();

	/**
	 * Слот, срабатывающий при нажатии кнопки "Сохранить как изображение" в главном меню.
	 */
	void saveAsPicture();

	/**
	 * Слот, срабатывающий при смене выделенного элемента в списке объектов.
	 */
	void objListCurRowChanged(int currentrow);

};

#endif // SUMLEDITOR_H
