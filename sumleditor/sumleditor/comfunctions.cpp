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

/** 
* Функция заставляет виджет мигать заданным цветом.
* @param widget Указатель на виджет
* @param color1 Ссылка на первый цвет
* @param color2 Ссылка на второй цвет
* @param times Количество раз
*/
void blink(QWidget* widget, QColor& color1,  QColor& color2, int times)
{
	for (int i = 0;i<times;i++)
	{
        fadeInto(widget, color2);
		QTest::qWait(200);

        fadeInto(widget, color1);
		QTest::qWait(200);
	}
}
