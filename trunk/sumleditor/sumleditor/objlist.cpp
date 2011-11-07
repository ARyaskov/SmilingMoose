#include "stdafx.h"
#include "volatile.h"
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
			{
				item->setText(name + " : " + desc);
			}
			else 
			{
				QString text;
				if ((name.length()) > 30) { text = name.remove(30, name.length() - 30); text += "..."; }
				else text = name;
				text.remove("\n");
				item->setText(text);
			}
			item->setIcon(QIcon(":/sumleditor/resources/L.bmp"));	
		}break;


	case COMMENT:
		{
			if (name.length())
				item->setText(name+" : "+desc);
			else
			{
				QString text = "";
				if ((desc.length()) > 30) { text = desc.remove(30, desc.length() - 30); text += "..."; }
				else text = desc;
				text.replace("\n", " ");
				item->setText(text);
			}
			item->setIcon(QIcon(":/sumleditor/resources/c.bmp"));
		}break;
	}
	list->addItem(item);
}

/**
* Функция удаляет указанный элемент из списка.
* @param list Указатель на  список
* @param id ID элемента в списке
*/
void delFromList(QListWidget* list, QString id)
{
    list->takeItem(rowById(list,id));
}

/**
* Функция возвращает номер строки элемента в виджете по его ID
* @param list Указатель на  список
* @param id ID элемента в списке
*/
int rowById(QListWidget* list, QString id)
{
    ElementMetaInfo meta;
	QVariant tempVar;
    int result = -1;

	for (int i=0;i<list->count();i++)
	{
		tempVar = list->item(i)->data(Qt::UserRole);
		meta = tempVar.value<ElementMetaInfo>();
	    if (meta.id == id)
		{
		   result = i;
		   break;
		}
	}
	return result;
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

