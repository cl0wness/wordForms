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

/*!
 *  \brief Сравнить списки строк.
 *
 *  Функция сравнивает два списка по строчно.
 *  param[in] list1 - первый список строк
 *  param[in] list2 - второй список строк
 *  return список номеров различных пар
*/
QList<int> cmpLists(QList<QString> &list1,QList<QString> &list2);


#endif // FUNCTIONS_H
