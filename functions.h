#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>

/*!
 *  \brief Разделить строку на слова.
 *
 *  Функция делит строку на слова. Разделительные знаки - знаки препинания и пробелы.
 *  param[in] str - исходная строка
 *  param[out] words - список слов
*/
void separByWords(QString str, QList<QString> &words);

#endif // FUNCTIONS_H
