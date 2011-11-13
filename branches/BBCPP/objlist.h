#pragma once
#ifndef OBJLIST_H
#define OBJLIST_H
/**
* Функция добавляет указанный элемент к списку объектов.
* @param list Указатель на список
* @param act Действие
* @param metainf Информация о конкретном элементе (Имя, id, расположение и т.д.)
*/
void addToObjList(QListWidget* list, enum Action act, const QVariant& metainf);

/**
* Функция удаляет указанный элемент из списка.
* @param list Указатель на  список
* @param id ID элемента в списке
*/
void delFromList(QListWidget* list, QString id);

/**
* Функция проверяет есть ли объект, подобный данному (одинаковое имя и структура)
* @param list Указатель на список
* @param act Действие
* @param metainf Информация об элементе для поиска
* @return Наличие подобного объекта в списке
*/
bool existDublicate(QListWidget* list, const QVariant& metainf);

/**
* Функция возвращает номер строки элемента в виджете по его ID
* @param list Указатель на  список
* @param id ID элемента в списке
*/
int rowById(QListWidget* list, QString id);

#endif