#include "stdafx.h"
#include "objlist.h"

/**
* Функция добавляет указанный элемент к древовидному списку объектов.
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация о конкретном элементе (Имя, id, расположение и т.д.)
*/
void addToObjList(QTreeWidget* list, enum Action act, const QVariant& metainf)
{
	switch (act)
	{
	case SELECT:{}break;
	case LIFELINE:
		{
			QString name = metainf.toString();
			QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name),0);
			item->setData(0, Qt::UserRole, metainf);
			item->setIcon(0,QIcon(":/sumleditor/resources/L.bmp"));
			list->addTopLevelItem(item);
		}break;

	}
}

/**
* Функция проверяет есть ли объект, подобный данному (одинаковое имя и структура)
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация об элементе для поиска
* @return Наличие подобного объекта в списке
*/
bool existDublicate(QTreeWidget* list, const QVariant& metainf)
{
	struct ElementMetaInfo meta = metainf.value<ElementMetaInfo>();
	QList<QTreeWidgetItem *> dubItems =  list->findItems( meta.name, Qt::MatchFixedString | Qt::MatchCaseSensitive );
	return !dubItems.isEmpty();
}