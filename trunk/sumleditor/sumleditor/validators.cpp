#include "stdafx.h"
#include "validators.h"


validatorNameLE::validatorNameLE(QObject *parent): QValidator(parent)
{

}

validatorNameLE::~validatorNameLE()
{

}

/** 
* ������� �������� ���������� ������.
* @param input ������ �� ��������� �����.
* @param pos ������� �������
*/
QValidator::State validatorNameLE::validate(QString & input, int & pos ) const
{
	QValidator::State result = QValidator::Acceptable;

	if (input.length() > 64 || input.contains('\"') || input.contains('\''))
		result = QValidator::Invalid;

	return result;
}
