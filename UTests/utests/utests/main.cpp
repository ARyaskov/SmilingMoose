#include <QtTest>
#include "freecommentfortest.h"
#include "lifelinefortest.h"

Q_DECLARE_METATYPE(FreeCommentForTest)
Q_DECLARE_METATYPE(LifelineForTest)

class Test_SUMLEditorProject : public QObject
{
	Q_OBJECT

private:

	/* Функция считывания xml файла в строку. */
	QString readXmlFile (QString filename)
	{
		QString result = "";
		QFile file(filename);

		if (file.open(QIODevice::ReadOnly))
		{
			QTextStream stream(&file);
			result = stream.readAll();
			file.close();
		}

		return result;
	}

	/* Сохранения свободного комментария в xml файла. */
	void save (QString filename, FreeCommentForTest fcft)
	{
		QDomDocument doc("test_comment");
		QDomElement domElement = doc.createElement("comments");
		doc.appendChild(domElement);

		QDomElement dom = fcft.save(doc);
		domElement.appendChild(dom);

		QFile file(filename);
		if (file.open(QIODevice::WriteOnly))
		{
			QTextStream(&file) << doc.toString();
			file.close();
		}
	}

	/* Сохранения свободного комментария в xml файла. */
	void save (QString filename, LifelineForTest llft)
	{
		QDomDocument doc("test_lifelines");
		QDomElement domElement = doc.createElement("lifelines");
		doc.appendChild(domElement);

		QDomElement dom = llft.save(doc, 0);
		domElement.appendChild(dom);

		QFile file(filename);
		if (file.open(QIODevice::WriteOnly))
		{
			QTextStream(&file) << doc.toString();
			file.close();
		}
	}

	/* Чтение свободного комментария из xml файла. */
	FreeCommentForTest load (QString filename)
	{
		FreeCommentForTest fcft;
		QDomDocument domDoc;
		QFile file(filename);

		if (file.open(QIODevice::ReadOnly))
		{
			if (domDoc.setContent(&file))
			{
				QDomNode node = domDoc.documentElement().firstChild();

				while (!node.isNull())
				{
					if (node.isElement())
					{
						QDomElement domElement = node.toElement();
						if (!domElement.isNull())
						{
							if (domElement.tagName() == "freecomment")
							{
								fcft.load(domElement);
							}
						}
					}
					node = node.nextSibling();
				}
			}
		}

		return fcft;
	}

	/* Функция проверки существования файла. */
	bool isFileExist (QString filename)
	{
		bool flag = true;
		QFile file(filename);

		if (!file.exists())
			flag = false;

		return flag;
	}

private slots:

	/* Тестирование сохранения в файл. */
	void createXml_data();
	void createXml();

	/* Тестирование считывания из файла. */
	void readXml_data();
	void readXml();

	/* Тестирование сохранения линии жизни в файл. */
	void writeLLtoXml_data();
	void writeLLtoXml();

};

void Test_SUMLEditorProject::createXml_data()
{
	QTest::addColumn<FreeCommentForTest>("comment");
	QTest::addColumn<QString>("xmlStr");
	QTest::addColumn<QString>("filename");

	FreeCommentForTest f1 = FreeCommentForTest();
	QString s2 = "firstTest.xml";
	QString s1 = QString("<!DOCTYPE test_comment>\n<comments>\n <freecomment x=\"-1\" y=\"-1\" z=\"-1\" name=\"name\" text=\"text\"/>\n</comments>\n");

	QTest::newRow("Test_1") << f1 << s1 << s2;

	FreeCommentForTest f12 = FreeCommentForTest("My text", "My name", 10, 11, 12);
	QString s22 = "firstTest.xml";
	QString s12 = QString("<!DOCTYPE test_comment>\n<comments>\n <freecomment x=\"10\" y=\"11\" z=\"12\" name=\"My name\" text=\"My text\"/>\n</comments>\n");

	QTest::newRow("Test_2") << f12 << s12 << s22;
}
void Test_SUMLEditorProject::createXml()
{
	QFETCH(FreeCommentForTest,comment);
	QFETCH(QString,xmlStr);
	QFETCH(QString,filename);

	save(filename,comment);
	QString result = readXmlFile(filename);

	QCOMPARE(xmlStr, result);
	QCOMPARE(isFileExist(filename),true);
}

void Test_SUMLEditorProject::readXml_data()
{
	QTest::addColumn<FreeCommentForTest>("comment");
	QTest::addColumn<QString>("filename");

	FreeCommentForTest f1 = FreeCommentForTest();
	QString s2 = "XML_Test_1.xml";

	QTest::newRow("Test_1") << f1 << s2;

	FreeCommentForTest f12 = FreeCommentForTest("My text", "My name", 10, 11, 12);
	QString s22 = "XML_Test_2.xml";

	QTest::newRow("Test_2") << f12 << s22;
}
void Test_SUMLEditorProject::readXml()
{
	QFETCH(FreeCommentForTest,comment);
	QFETCH(QString,filename);

	FreeCommentForTest result = load(filename);

	QCOMPARE(comment.operator ==(result), true);
}

void Test_SUMLEditorProject::writeLLtoXml_data()
{
	QTest::addColumn<LifelineForTest>("ll");
	QTest::addColumn<QString>("xmlStr");
	QTest::addColumn<QString>("filename");

	LifelineForTest l1 = LifelineForTest();
	QString s2 = "firstllTest.xml";
	QString s1 = QString("<!DOCTYPE test_lifelines>\n<lifelines>\n <lifeline x=\"-1\" y=\"-1\" z=\"-1\" description=\"description\" is_end=\"0\" id=\"0\" name=\"name\"/>\n</lifelines>\n");

	QTest::newRow("Test_1") << l1 << s1 << s2;

	LifelineForTest l2 = LifelineForTest("qqq", "ddd", true, 10, 20, 30);
	QString s12 = QString("<!DOCTYPE test_lifelines>\n<lifelines>\n <lifeline x=\"10\" y=\"20\" z=\"30\" description=\"ddd\" is_end=\"1\" id=\"0\" name=\"qqq\"/>\n</lifelines>\n");

	QTest::newRow("Test_2") << l2 << s12 << s2;

	LifelineForTest l3 = LifelineForTest("www", "fff", false, 90, 78, 34);
	QString s3 = QString("<!DOCTYPE test_lifelines>\n<lifelines>\n <lifeline x=\"90\" y=\"78\" z=\"34\" description=\"fff\" is_end=\"0\" id=\"0\" name=\"www\"/>\n</lifelines>\n");

	QTest::newRow("Test_3") << l3 << s3 << s2;
}
void Test_SUMLEditorProject::writeLLtoXml()
{
	QFETCH(LifelineForTest,ll);
	QFETCH(QString,xmlStr);
	QFETCH(QString,filename);

	save(filename,ll);
	QString result = readXmlFile(filename);

	QCOMPARE(xmlStr, result);
	QCOMPARE(isFileExist(filename),true);
}

QTEST_MAIN(Test_SUMLEditorProject)
#include "main.moc"