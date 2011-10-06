#include <QtTest>
#include "freecommentfortest.h"

Q_DECLARE_METATYPE(FreeCommentForTest)

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

QTEST_MAIN(Test_SUMLEditorProject)
#include "main.moc"