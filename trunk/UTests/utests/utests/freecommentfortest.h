#ifndef FREECOMMENTFORTEST_H
#define FREECOMMENTFORTEST_H

#include <QString>
#include <QtXml>

class FreeCommentForTest
{
public:

	/* Конструктор по умолчанию. */
	FreeCommentForTest();

	/* Конструктор с параметрами. */
	FreeCommentForTest(QString _text, QString _name, int _x, int _y, int _z);

	/* Деструктор. */
	~FreeCommentForTest();

	/* Метод сохранения комментария в xml файл. */
	QDomElement save (QDomDocument & domDoc) const;

private:

	/* Поля в данном классе только необходимые для тестирования. */
	QString text;
	QString name;
	int x, y, z;
	
};

#endif // FREECOMMENTFORTEST_H
