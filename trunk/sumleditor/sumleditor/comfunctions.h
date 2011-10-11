#ifndef COMFUNCTIONS_H
#define COMFUNCTIONS_H
#include <QtGui>
#include <QtTest>



class FreeComment;
class GraphWidget;
class Sumleditor;
class Lifeline;

/** 
* Функция меняет цвет выбранного виджета.
* @param widget Указатель на виджет
* @param color Ссылка на нужный цвет
*/
void fadeInto(QWidget* widget, QColor& color);

/** 
* Функция заставляет виджет мигать заданным цветом.
* @param widget Указатель на виджет
* @param color1 Ссылка на первый цвет
* @param color2 Ссылка на второй цвет
* @param times Количество раз
*/
void blink(QWidget* widget, QColor& color1, QColor& color2, int times);

#include "graphwidget.h"
#include "lifeline.h"
#include "freecomment.h"
#include "sumleditor.h"

#endif