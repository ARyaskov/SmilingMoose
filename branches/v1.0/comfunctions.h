#ifndef COMFUNCTIONS_H
#define COMFUNCTIONS_H

class FreeComment;
class GraphWidget;
class Sumleditor;
class Lifeline;

/** 
* ������� ������ ���� ���������� �������.
* @param widget ��������� �� ������
* @param color ������ �� ������ ����
*/
void fadeInto(QWidget* widget, QColor color);

/** 
* ������� ���������� ������ ������ �������� ������.
* @param widget ��������� �� ������
* @param color1 ������ �� ������ ����
* @param color2 ������ �� ������ ����
* @param times ���������� ���
*/
void blink(QWidget* widget, QColor& color1, QColor& color2, int times);

#endif
