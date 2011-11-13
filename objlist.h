#pragma once
#ifndef OBJLIST_H
#define OBJLIST_H
/**
* ������� ��������� ��������� ������� � ������ ��������.
* @param list ��������� �� ������
* @param act ��������
* @param metainf ���������� � ���������� �������� (���, id, ������������ � �.�.)
*/
void addToObjList(QListWidget* list, enum Action act, const QVariant& metainf);

/**
* ������� ������� ��������� ������� �� ������.
* @param list ��������� ��  ������
* @param id ID �������� � ������
*/
void delFromList(QListWidget* list, QString id);

/**
* ������� ��������� ���� �� ������, �������� ������� (���������� ��� � ���������)
* @param list ��������� �� ������
* @param act ��������
* @param metainf ���������� �� �������� ��� ������
* @return ������� ��������� ������� � ������
*/
bool existDublicate(QListWidget* list, const QVariant& metainf);

/**
* ������� ���������� ����� ������ �������� � ������� �� ��� ID
* @param list ��������� ��  ������
* @param id ID �������� � ������
*/
int rowById(QListWidget* list, QString id);

#endif