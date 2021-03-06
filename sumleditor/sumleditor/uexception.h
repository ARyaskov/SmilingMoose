#pragma once

#include <string>

using namespace std;
/**
@class SUMLEditorException
����� ����������. ���������� ������������ ��� ��� ������������ ����������.
*/
class SUMLEditorException
{

private:

	/// ���������� ���������� ����, ������ ��������� ����������.
	string msg;

public:

	/// ����������� �� ���������.
	SUMLEditorException() : msg("Unknown exception!")
	{
	}

	/// ����������� � ����������.
	/// @param str - ��������� ����������.
	SUMLEditorException(char* str) : msg(str)
	{
	}

	/// ����� ���������� ��������� ����������.
	/// @return ��������� ����������.
	string message ()
	{
		return msg;
	}

};

/**
* @function writeErrors
* ������� ���������� ��������� ������ � ���� (errors.txt), ��� ����������� ������� � ������������� ��������.
* @param message - ������, ���������� ����� ������.
*/
void writeErrors (string message)
{
    FILE* file;

	fopen_s(&file, "errors.txt", "at");

	fprintf(file,"\n");
	fprintf(file,"\n%s\n",__DATE__); // ������ ������� ����
	fprintf(file,"\n%s", message.c_str());

	fclose(file);
};

/**
* @function writeLogMessage
* ������� ����� ��� ���������.
* @param message - ������, ���������� ����� ���� - ���������.
*/
void writeLogMessage (string message)
{
    FILE* file;

	fopen_s(&file, "log.txt", "at");

	fprintf(file, "--- %s ---\n", message.c_str());

	fclose(file);
}
