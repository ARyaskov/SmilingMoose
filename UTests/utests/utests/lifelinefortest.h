#ifndef LIFELINEFORTEST_H
#define LIFELINEFORTEST_H

#include <QString>
#include <QtXml>

class LifelineForTest
{
public:

	/* ����������� �� ���������. */
	LifelineForTest();

	/* ����������� � �����������. */
	LifelineForTest(QString _name, QString _description, bool _isEnd, int _x, int _y, int _z);

	/* ����������. */
	~LifelineForTest();

	/* ����� ���������� ����� ����� � xml ����. */
	QDomElement save(QDomDocument & domDoc, int id) const;

	/* ���������� ��������� ���������. */
	bool operator== (const LifelineForTest & other) const;

private:
	
	/* ���� ������ */
	QString name;
	QString description;
	bool isEnd;
	int x;
	int y;
	int z;

};

#endif // LIFELINEFORTEST_H
