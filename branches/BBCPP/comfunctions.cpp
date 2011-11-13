#include "stdafx.h"
#include "volatile.h"


/** 
* Функция меняет цвет выбранного виджета.
* @param widget Указатель на виджет
* @param color Ссылка на нужный цвет
*/
void fadeInto(QWidget* widget, QColor color)
{

	QPalette palette( widget->palette() );
	palette.setColor( QPalette::Base, color );
	widget->setPalette(palette);
}


