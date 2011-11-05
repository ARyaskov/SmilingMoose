#include "graphwidget.h"

/**
* ������� ��������� ��������� ������� � ������������ ������ ��������.
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� � ���������� �������� (���, id, ������������ � �.�.)
*/
void addToObjList(QListWidget* list, enum Action act, const QVariant& metainf);

/**
* ������� ��������� ���� �� ������, �������� ������� (���������� ��� � ���������)
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� �� �������� ��� ������
* @return ������� ��������� ������� � ������
*/
bool existDublicate(QListWidget* list, const QVariant& metainf);

