#pragma once

#include <string>

using namespace std;
/**
@class SUMLEditorException
Класс исключений. Необходимо использовать его при выбрасывании исключений.
*/
class SUMLEditorException
{

private:

	/// Переменная строкового типа, хранит сообщение исключения.
	string msg;

public:

	/// Конструктор по умолчанию.
	SUMLEditorException() : msg("Unknown exception!")
	{
	}

	/// Конструктор с параметром.
	/// @param str - сообщение исключения.
	SUMLEditorException(char* str) : msg(str)
	{
	}

	/// Метод возвращает сообщение исключения.
	/// @return Сообщение исключения.
	string message ()
	{
		return msg;
	}

};

/**
* @function writeErrors
* Функция записывает сообщение ошибки в файл (errors.txt), для последующей отладки и сопровождения продукта.
* @param message - строка, содержащая текст ошибки.
*/
void writeErrors (string message)
{
	FILE* file = fopen("errors.txt", "at");

	fprintf(file,"\n");
	fprintf(file,"\n%s\n",__DATE__); // Запись текущей даты
	fprintf(file,"\n%s", message.c_str());

	fclose(file);
};

/**
* @function writeLogMessage
* Функция ведет лог программы.
* @param message - строка, содержащая текст лога - сообщения.
*/
void writeLogMessage (string message)
{
	FILE* file = fopen("log.txt", "at");

	fprintf(file, "--- %s ---\n", message.c_str());

	fclose(file);
}