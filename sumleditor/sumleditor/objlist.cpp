#include "stdafx.h"
#include "objlist.h"

/**
* ������� ��������� ��������� ������� � ������������ ������ ��������.
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� � ���������� �������� (���, id, ������������ � �.�.)
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
* ������� ��������� ���� �� ������, �������� ������� (���������� ��� � ���������)
* @param list ��������� �� ����������� ������
* @param act ��������
* @param metainf ���������� �� �������� ��� ������
* @return ������� ��������� ������� � ������
*/
bool existDublicate(QTreeWidget* list, const QVariant& metainf)
{
	struct ElementMetaInfo meta = metainf.value<ElementMetaInfo>();
	QList<QTreeWidgetItem *> dubItems =  list->findItems( meta.name, Qt::MatchFixedString | Qt::MatchCaseSensitive );
	return !dubItems.isEmpty();
}