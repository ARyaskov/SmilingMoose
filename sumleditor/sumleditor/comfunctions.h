#ifndef COMFUNCTIONS_H
#define COMFUNCTIONS_H
#include <QtGui>
#include <QtTest>



class FreeComment;
class GraphWidget;
class Sumleditor;
class Header;

/** 
* ������� ������ ���� ���������� �������.
* @param widget ��������� �� ������
* @param color ������ �� ������ ����
*/
void fadeInto(QWidget* widget, QColor& color);

/** 
* ������� ���������� ������ ������ �������� ������.
* @param widget ��������� �� ������
* @param color1 ������ �� ������ ����
* @param color2 ������ �� ������ ����
* @param times ���������� ���
*/
void blink(QWidget* widget, QColor& color1, QColor& color2, int times);

#include "graphwidget.h"
#include "header.h"
#include "freecomment.h"
#include "sumleditor.h"

#endif