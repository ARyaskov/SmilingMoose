#include "graphwidget.h"

/**
* ������� ��������� ��������� ������� � ������������ ������ ��������.
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� � ���������� �������� (���, id, ������������ � �.�.)
*/
void addToObjList(QTreeWidget* list, enum Action act, const QVariant& metainf);

/**
* ������� ��������� ���� �� ������, �������� ������� (���������� ��� � ���������)
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� �� �������� ��� ������
* @return ������� ��������� ������� � ������
*/
bool existDublicate(QTreeWidget* list, const QVariant& metainf);