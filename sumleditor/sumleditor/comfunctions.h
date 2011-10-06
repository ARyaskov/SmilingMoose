#ifndef COMFUNCTIONS_H
#define COMFUNCTIONS_H
#include <QtGui>
#include <QtTest>

/** ���� ��������� "��������������" */
QColor warning_color;

/** ���� ��������� "������" */
QColor error_color;

/** ���� ��������� "��������" */
QColor attention_color;

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

#endif