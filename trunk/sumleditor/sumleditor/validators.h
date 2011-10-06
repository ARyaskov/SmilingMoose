
#ifndef VALIDATORS_H
#define VALIDATORS_H
#include <QValidator>

/**
 * Класс, описывающий валидатор строки ввода имени
 */
class validatorNameLE : public QValidator
{
	Q_OBJECT

public:
	validatorNameLE(QObject *parent);

	~validatorNameLE();
	
	/** 
	 * Функция проверки введенного текста.
	 * @param input Ссылка на введенный текст.
	 * @param pos Позиция каретки
	 */
	QValidator::State validate(QString & input, int &pos ) const;	

};

#endif