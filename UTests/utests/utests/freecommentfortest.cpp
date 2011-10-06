#include "freecommentfortest.h"

FreeCommentForTest::FreeCommentForTest()
{
	text = "text";
	name = "name";
	x = -1;
	y = -1;
	z = -1;
}

FreeCommentForTest::FreeCommentForTest(QString _text, QString _name, int _x, int _y, int _z)
{
	text = _text;
	name = _name;
	x = _x;
	y = _y;
	z = _z;
}

FreeCommentForTest::~FreeCommentForTest()
{

}

QDomElement FreeCommentForTest::save(QDomDocument &domDoc) const
{
	QDomElement element = domDoc.createElement("freecomment");

	QDomAttr attr = domDoc.createAttribute("text");
	attr.setValue(text.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("name");
	attr.setValue(name.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("x");
	attr.setValue(QString::number(x));
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("y");
	attr.setValue(QString::number(y));
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("z");
	attr.setValue(QString::number(z));
	element.setAttributeNode(attr);

	return element;
}

void FreeCommentForTest::load (const QDomElement & element)
{
	text = element.attribute("text", "text");
	name = element.attribute("name", "name");
	x    = element.attribute("x", "-1").toInt();
	y    = element.attribute("y", "-1").toInt();
	z    = element.attribute("z", "-1").toInt();
}

bool FreeCommentForTest::operator ==(const FreeCommentForTest &other) const
{
	bool flag = false;

	if (text == other.text && name == other.name &&
		x == other.x && y == other.y && z == other.z)
		flag = true;

	return flag;
}