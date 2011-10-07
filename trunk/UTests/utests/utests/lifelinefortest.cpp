#include "lifelinefortest.h"

LifelineForTest::LifelineForTest()
{
	name = "name";
	description = "description";
	isEnd = false;
	x = -1;
	y = -1;
	z = -1;
}

LifelineForTest::LifelineForTest(QString _name, QString _description,
								 bool _isEnd, int _x, int _y, int _z)
{
	name = _name;
	description = _description;
	isEnd = _isEnd;
	x = _x;
	y = _y;
	z = _z;
}

LifelineForTest::~LifelineForTest()
{

}

QDomElement LifelineForTest::save(QDomDocument &domDoc, int id) const
{
	QDomElement element = domDoc.createElement("lifeline");

	QDomAttr attr = domDoc.createAttribute("description");
	attr.setValue(description.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("name");
	attr.setValue(name.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("is_end");
	attr.setValue(QString::number(isEnd));
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

	attr = domDoc.createAttribute("id");
	attr.setValue(QString::number(id));
	element.setAttributeNode(attr);

	return element;
}

bool LifelineForTest::operator ==(const LifelineForTest &other) const
{
	bool flag = false;

	if (name == other.name && description == other.description &&
		isEnd == other.isEnd && x == other.x && y == other.y && z == other.z)
		flag = true;

	return flag;
}