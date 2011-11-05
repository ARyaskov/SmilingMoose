#include "stdafx.h"
#include "objlist.h"

/**
* ������� ��������� ��������� ������� � ������������ ������ ��������.
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� � ���������� �������� (���, id, ������������ � �.�.)
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
* ������� ��������� ���� �� ������, �������� ������� (���������� ��� � ���������)
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� �� �������� ��� ������
* @return ������� ��������� ������� � ������
*/
bool existDublicate(QListWidget* list, const QVariant& metainf)
{
	struct ElementMetaInfo meta = metainf.value<ElementMetaInfo>();
	QList<QListWidgetItem *> dubItems =  list->findItems( meta.name, Qt::MatchFixedString | Qt::MatchCaseSensitive );
	return !dubItems.isEmpty();
}

