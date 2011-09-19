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