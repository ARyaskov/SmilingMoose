#ifndef LIFELINEFORTEST_H
#define LIFELINEFORTEST_H

#include <QString>
#include <QtXml>

class LifelineForTest
{
public:

	/* Конструктор по умолчанию. */
	LifelineForTest();

	/* Конструктор с параметрами. */
	LifelineForTest(QString _name, QString _description, bool _isEnd, int _x, int _y, int _z);

	/* Деструктор. */
	~LifelineForTest();

	/* Метод сохранения линии жизни в xml файл. */
	QDomElement save(QDomDocument & domDoc, int id) const;

	/* Перегрузка оператора сравнения. */
	bool operator== (const LifelineForTest & other) const;

private:
	
	/* Поля класса */
	QString name;
	QString description;
	bool isEnd;
	int x;
	int y;
	int z;

};

#endif // LIFELINEFORTEST_H
