#pragma once
#ifndef VALIDATORS_H
#define VALIDATORS_H


/**
 * �����, ����������� ��������� ������ ����� �����
 */
class validatorNameLE : public QValidator
{
	Q_OBJECT

public:
	validatorNameLE(QObject *parent);

	~validatorNameLE();
	
	/** 
	 * ������� �������� ���������� ������.
	 * @param input ������ �� ��������� �����.
	 * @param pos ������� �������
	 */
	QValidator::State validate(QString & input, int & pos ) const;	

};

#endif