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


