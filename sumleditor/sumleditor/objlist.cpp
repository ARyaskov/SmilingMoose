#include "stdafx.h"
#include "objlist.h"

/**
* Функция добавляет указанный элемент к древовидному списку объектов.
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация о конкретном элементе (Имя, id, расположение и т.д.)
*/
void addToObjList(QListWidget* list, enum Action act, const QVariant& metainf)
{
	ElementMetaInfo meta = metainf.value<ElementMetaInfo>();
	QString name = meta.name;
	QString desc = meta.desc;
	QListWidgetItem* item = new QListWidgetItem();
	item->setData(Qt::UserRole, metainf);

	switch (act)
	{
	case SELECT:{}break;
	case LIFELINE:
		{
			if (desc.length())
				item->setText(name+" : "+desc);
			else
				item->setText(name);
			item->setIcon(QIcon(":/sumleditor/resources/L.bmp"));	
		}break;


	case COMMENT:
		{
			if (name.length())
				item->setText(name+" : "+desc);
			else
				item->setText(desc);
			item->setIcon(QIcon(":/sumleditor/resources/c.bmp"));
		}break;
	}
	list->addItem(item);
}

/**
* Функция проверяет есть ли объект, подобный данному (одинаковое имя и структура)
* @param list Указатель на древовидный список
* @param act Действие
* @param metainf Информация об элементе для поиска
* @return Наличие подобного объекта в списке
*/
bool existDublicate(QListWidget* list, const QVariant& metainf)
{
	struct ElementMetaInfo meta = metainf.value<ElementMetaInfo>();
	QList<QListWidgetItem *> dubItems =  list->findItems( meta.name, Qt::MatchFixedString | Qt::MatchCaseSensitive );
	return !dubItems.isEmpty();
}

