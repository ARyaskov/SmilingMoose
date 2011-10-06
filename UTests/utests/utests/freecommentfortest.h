#ifndef FREECOMMENTFORTEST_H
#define FREECOMMENTFORTEST_H

#include <QString>
#include <QtXml>

class FreeCommentForTest
{
public:

	/* ����������� �� ���������. */
	FreeCommentForTest();

	/* ����������� � �����������. */
	FreeCommentForTest(QString _text, QString _name, int _x, int _y, int _z);

	/* ����������. */
	~FreeCommentForTest();

	/* ����� ���������� ����������� � xml ����. */
	QDomElement save (QDomDocument & domDoc) const;

private:

	/* ���� � ������ ������ ������ ����������� ��� ������������. */
	QString text;
	QString name;
	int x, y, z;
	
};

#endif // FREECOMMENTFORTEST_H
