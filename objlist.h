#include "graphwidget.h"

/**
* Функция добавляет указанный элемент к древовидному списку объектов.
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация о конкретном элементе (Имя, id, расположение и т.д.)
*/
void addToObjList(QListWidget* list, enum Action act, const QVariant& metainf);

/**
* Функция проверяет есть ли объект, подобный данному (одинаковое имя и структура)
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация об элементе для поиска
* @return Наличие подобного объекта в списке
*/
bool existDublicate(QListWidget* list, const QVariant& metainf);

