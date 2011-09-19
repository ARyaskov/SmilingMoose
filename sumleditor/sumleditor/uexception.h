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