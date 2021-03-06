#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>

/// Характер ошибки
enum Mistake
{
    WRONG_FORM, ///< неправильно выбранная форма
    WRONG_WORD, ///< неправильно выбранное слово
    WRONG_EXCEPTION, ///< неправильно создана форма-исключение
    WRONG_CREATE, ///< неправильно создана обычная форма
    WRONG_FORMER, ///< нeправильно выбранный формообразователь
    NO_MISTAKE ///< нет ошибки
};

/*!
 *  \brief Разделить строку на слова
 *
 *  Функция делит строку на слова. Разделительные знаки - знаки препинания и пробелы.
 *  \param[in] str исходная строка
 *  \param[out] words список слов
*/
void separByWords(QString str, QList<QString> &words);

/*!
 *  \brief Сравнить списки строк
 *
 *  Функция сравнивает два списка по строчно.
 *  \param[in] list1 первый список строк
 *  \param[in] list2 второй список строк
 *  \return список номеров различных пар
*/
QList<int> cmpLists(QList<QString> &list1,QList<QString> &list2);

/*!
 *  \brief Получить различие концов двух слов
 *
 *  Функция обрезает слова с начала до первого расхождения
 *  \param[in,out] first первое слово
 *  \param[in,out] second второе слово
 *  \return количество удалённых букв
*/
int getEndDifference(QString &first, QString &second);

/*!
 *  \brief Сравнить строку со списком
 *
 *  Функция находит совпадение строки с одной из строк списка.
 *  \param[in] str исходная строка
 *  \param[in] list список
 *  \return линия списка, на которой случилось совпадение со строкой. -1, если совпадения нет.
*/
int cmpWithList(QString str, QList <QString> list);

/*!
 *  \brief Сравнить строку с набором словарей
 *
 *  Функция находит совпадение строки с набором из нескольких словарей.
 *  \param[in] str исходная строка
 *  \param[in] dictionaries набор словарей
 *  \param[out] dictPos найденное совпадение {номер словаря, номер строки в словаре}
 *  \return успешность сравнения
*/
bool cmpWithDicts(QString str, const QList <QList <QStringList>> dictionaries, int dictPos[2]);

/*!
 *  \brief Убрать формообразователь слова для соотвествия словарю
 *
 *  Функция отрезает от слова возможные формообразователи, чтобы слово могло соответствовать словарной строке.
 *  \param[in,out] wrong слово для преобразования
 *  \param[in] dictLine словарная строка
*/
void removeUnfitFormer(QString &wrong, QList <QString> dictLine);

/*!
 *  \brief Идентифицировать словарную ошибку
 *
 *  Функция определяет характер словарной ошибки.
 *  \param[in] wrong слово с ошибкой
 *  \param[in] dictLine словарная строка, где есть правильное слово
 *  \param[in] correct правильное слово
 *  \return ошибка
*/
Mistake identifyDictMistake(QString wrong, QList <QString> dictLine, const QString correct);

/*!
 *  \brief Идентифицировать обычную (несловарную) ошибку
 *
 *  Функция определяет характер обычной ошибки. Обычная ошибка - ошибка при создании формы по обычному правилу.
 *  \param[in] correct правильное слово
 *  \param[in] wrong слово с ошибкой
 *  \return ошибка
*/
Mistake identifyUsualMistake(QString correct, QString wrong);

/*!
 *  \brief Идентифицировать ошибку в слове
 *
 *  Функция определяет характер ошибки, в соответствии с её типом - словарная или обычная.
 *  \param[in] correct правильное слово
 *  \param[in] wrong слово с ошибкой
 *  \return ошибка
*/
Mistake identifyMistake(QString correct, QString wrong);

/*!
 *  \brief Сформулировать ошибку
 *
 *  Функция формирует читаемую строку с объяснением ошибки по её характеру.
 *  \param[in] mistake ошибка
 *  \return строка с формулировкой
*/
QString formulateMistake(Mistake mistake);

/*!
 *  \brief Перестроить сокращенное отрицание
 *
 *  Функция перестраивает все сокращенные отрицания строке. (глагол)n't -> (глагол) not.
 *  \param[in,out] str строка
*/
void rearrangeNegatives(QString &str);

/*!
 *  \brief Загрузить данные из файла
 *
 *  Функция выгружает текстовые данные из файла.
 *  \param[in] filePath путь до файла
 *  \return список строк из файла
 *  \throw 0 в случае проблем при работе с входным файлом
*/
QStringList loadFile (QString filePath);

/*!
 *  \brief Сохранить данные в файл
 *
 *  Функция загружает текстовые данные в файл.
 *  \param[in] filePath путь до файла
 *  \param[in] text текст для сохранения
 *  \throw 1 в случае проблем при работе с выходным файлом
*/
void saveToFile(QString filePath, QStringList text);

#endif // FUNCTIONS_H
