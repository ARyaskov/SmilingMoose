#include "stdafx.h"
#include "volatile.h"


/** 
* ������� ������ ���� ���������� �������.
* @param widget ��������� �� ������
* @param color ������ �� ������ ����
*/
void fadeInto(QWidget* widget, QColor color)
{

	QPalette palette( widget->palette() );
	palette.setColor( QPalette::Base, color );
	widget->setPalette(palette);
}

/** 
* ������� ���������� ������ ������ �������� ������.
* @param widget ��������� �� ������
* @param color1 ������ �� ������ ����
* @param color2 ������ �� ������ ����
* @param times ���������� ���
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
