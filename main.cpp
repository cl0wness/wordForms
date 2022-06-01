#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include "functions.h"
#include "dictionaries.h"

int main(int argc, char *argv[])
{
    QCoreApplication comLine(argc, argv); // аргументы командной строки
    QString input, output; // входной и выходной файл
    QStringList strings, explainsMistake; // предложения и объяснения ошибок
    QList <Mistake> mistakesIn; // позиции ошибок

    bool haveMistake = false; // наличие ошибок
    try
    {
        // Получить пути к входному и выходному файлам, если задано достаточно аргементов
        if(comLine.arguments().size()>2)
        {
            input = comLine.arguments().at(1);
            output = comLine.arguments().at(2);
        }
        // Иначе - исключение 0
        else
            throw 0;
        // Загрузить данные из входного файла
        strings = loadFile(input);
        // Исключение 4, если строка одна, но в ней два предложения
        if (strings.count() == 1 && strings[0].contains(QRegExp("[.?!].+[.?!]")))
        {
            throw 4;
        }
        // Иначе, если строк меньше 2, исключение 2
        else if (strings.count() < 2)
            throw 2;
        // Иначе, если строк больше 2, исключение 2
        else if (strings.count() > 2)
            throw 3;
        // Перестроить отрицания в предложениях
        rearrangeNegatives(strings[0]);
        rearrangeNegatives(strings[1]);
        // Разделить предложения на слова
        QList<QString> str1, str2;
        separByWords(strings[0],str1);
        separByWords(strings[1],str2);
        // Исключение 5, если в предложениях разной количество слов
        if(str1.count() != str2.count())
            throw 5;
        // Сравнить слова попарно
        QList<int> diffPairs = cmpLists(str1,str2);
        haveMistake = !diffPairs.isEmpty();
        // Если есть несовпадения в парах
        if(haveMistake)
        {
            // Для каждой несовпадающей пары
            for(int i = 0; i<diffPairs.count(); i++)
            {
                // Идентифицировать ошибку
                mistakesIn << identifyMistake(str1[diffPairs[i]], str2[diffPairs[i]]);
                // Сформировать строку-объяснение
                QString explain = str2[diffPairs[i]];
                explain.append(" - ").append(formulateMistake(mistakesIn[i])).append(" - ").append(str1[diffPairs[i]]).append("\n");
                explainsMistake << explain;
            }
        }
        // Иначе - ошибок не найдено
        else {
            explainsMistake << "Ошибок не найдено.";
        }
        // Сохранить результаты в выходной файл
        saveToFile(output, explainsMistake);
    }
    catch (int error)
    {
        QStringList exception;
        // Обработать исключения
        switch (error)
        {
            case 0: exception << "Неверно указан файл с входными данными. Возможно, файл не существует или нет прав к доступу.";
                    break;
            case 1: exception << "Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись.";
                    break;
            case 2: exception << "В указанном файле недостаточно данных. Введите два предложения на отдельных строках.";
                    break;
            case 3: exception << "В указанном файле содержатся лишние данные. Введите два предложения на отдельных строках.";
                    break;
            case 4: exception << "В указанном файле недостаточно данных. Возможно, предложения записаны на одной строке.";
                    break;
            case 5: exception << "Предложения в указанном файле различны по составу. Проверьте входные данные.";
        }
        try {
            // Сохранить исключения в выходной файл
            saveToFile(output, exception);
        } catch (int error) {
            // Напечатать предупреждение, если нет доступа к выходному файлу
            if(error == 1)
                qWarning("Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись.");
        }
    }
    return 0;
    return comLine.exec();
}

void separByWords(QString str, QList<QString> &words)
{
    //..Считать слово не найденным
    int wordLenght = 0;
    // Пока поиск не дошёл до конца предложения
    while (wordLenght != -1)
    {
        QString word;
        //Найти место разделяющего знака (знака препинания или пробела)
        wordLenght = str.indexOf(QRegExp("[ ,-;.!?\"]"));
        //Скопировать слово до этого знака
        word = str.left(wordLenght);
        //Перевести слово в нижний регистр
        word = word.toLower();
        //Записать в итоговые слова, если слово имеется
        if(!word.isEmpty())
            words << word;
        //Удалить слово из предложения
        str.remove(0, wordLenght+1);
    }
}

QList<int> cmpLists(QList<QString> &list1,QList<QString> &list2)
{
    QList<int> difPairs;
    //Для каждой пары слов в списках
    for(int i = 0; i<list1.count(); i++)
    {
        //Записать номер пары, если слова различны
        if(list1[i]!=list2[i])
             difPairs << i;
    }
    return difPairs;
}

int getEndDifference(QString &first, QString &second)
{
    int delLetters = 0;
    //..Считать слова одинаковыми
    bool equal = true;
    // Пока слова одинаковые и в них остались символы
    while(equal && first.length()>0 && second.length()>0)
    {
        // Удалить текущие символы, если они равны
        if(first[0] == second[0])
        {
            first.remove(0,1);
            second.remove(0,1);
            delLetters++;
        }
        // Иначе считать слова неодинаковыми
        else
            equal = false;
    }
    return delLetters;
}

int cmpWithList(QString str, QList <QString> list)
{
    int hit;                            // попадание в список
    // Для каждого слова из списка
    for(int i = 0; i<list.count(); i++)
    {
        // Если позиция списка имеет равноправные значения
        if(list[i].contains('/'))
            // Сравнить исходную строку с обоими значениями
            hit = (str.compare(list[i].left(list[i].indexOf('/'))))*
                  (str.compare(list[i].right(list[i].length() - list[i].indexOf('/')-1)));
        // Иначе
        else
            // Сравнить исходную строку с позицией в списке
            hit = str.compare(list[i]);
        // Вернуть позицию в списке, если есть попадание
        if(hit == 0)
            return i;
    }
    return -1;
}

bool cmpWithDicts(QString str, const QList <QList <QStringList>> dictionaries, int dictPos[2])
{
    int line = -1;                                      // строка словаря
    int dict = 0;                                       // номер словаря
    int hit = -1;                                       // попадание
    // Для каждого словаря и пока не найдено совпадение со строкой
    for(dict = 0; dict<dictionaries.count() && (hit == -1); dict++)
    {
        // Для каждой строки в словаре и пока не найдено совпадение
        for (line = 0; line < dictionaries[dict].count() && (hit == -1); line++)
        {
            // Сравнить строку со строкой словаря
            hit = cmpWithList(str,dictionaries[dict][line]);
        }
    }
    // Если совпадение найдено
    if(hit != -1)
    {
        // Считать сравнение успешным
        dictPos[0] = dict-1;
        dictPos[1] = line-1;
        return true;
    }
    // Иначе считать сравнение неуспешным
    else
        return false;
}

void removeUnfitFormer(QString &wrong, QList <QString> dictLine)
{
    if(wrong.right(4) == "self")                     // Если слово является возвратным местоимением
        wrong.remove(wrong.length()-4, 4);                 // Убрать возратный суффикс
    else if(wrong.right(6) == "selves")
            wrong.remove(wrong.length()-6, 6);
    // Если нового слова нет в словарной строке
    if(cmpWithList(wrong, dictLine) == -1)
    {
        // Если слово является 4-ой формой глагола
        if(wrong.right(3) == "ing")
        {
            // Удалить формообразователь
            wrong.remove(wrong.length()-3, 3);
            if(dictLine[0].right(1) == "e")
                wrong.append("e");
        }
        // Иначе если слово - наречие или превосходная степени прилагательного
        else if(wrong.right(2) == "ly" || wrong.right(2) == "st")
            // Удалить формообразователь
            wrong.remove(wrong.length()-2, 2);
        // Иначе если у слова есть окончание-суффикс
        else if(wrong.right(1) == "s" || wrong.right(1) == "r" || wrong.right(1) == "d")
            // Удалить окончание-суффикс
            wrong.remove(wrong.length()-1, 1);

        // Если данной формы нет в словарной строке
        if(cmpWithList(wrong, dictLine) == -1)
        {
            // Удалить доп. окончание-суффикс, если оно есть
            if(wrong.right(1) == "e")
                wrong.remove(wrong.length()-1, 1);
            // Если данной формы всё ещё нет в словарной строке
            if(cmpWithList(wrong, dictLine) == -1)
            {
                // Изменить преобразованное окончание-суффикс, если оно есть
                if(wrong.right(1) == "i")
                    wrong.replace(wrong.length()-1, 1, 'y');
            }
        }
    }
}

Mistake identifyDictMistake(QString wrong, QList <QString> dictLine, const QString correct)
{
    QString fullWrong = wrong;                                  // копия неправильного слова
    // Если неправильное слово есть в словарной строке
    if(cmpWithList(wrong, dictLine) != -1)
    {
        // Считать, что ошибки нет, если слова равноправны
        if(cmpWithList(wrong, dictLine) == cmpWithList(correct, dictLine))
            return NO_MISTAKE;
        // Иначе считать, что ошибка в выборе формы слова
        else
            return WRONG_FORM;
    }
    // Иначе
    else
        // Убрать мешающий совпадению формообразователь
        removeUnfitFormer(wrong, dictLine);

    // Если неправильное слово теперь есть в словарной строке
    if(cmpWithList(wrong, dictLine)!= -1)
    {
        // Считать, что ошибка в выборе формы, если неправильное 4-ая форма глагола
        if(fullWrong.right(3) == "ing")
            return WRONG_FORM;
        // Иначе считать, что ошибка в создании формы-исключения
        else
            return WRONG_EXCEPTION;
    }
    // Иначе считать, что ошибка в выборе слова (слово другое)
    else
        return WRONG_WORD;
}

Mistake identifyUsualMistake(QString correct, QString wrong)
{
    // Обрезаем слова до первого расхождения
    QString fullCorrect = correct;
    int delLetters = getEndDifference(correct, wrong);
    // Считать, что ошибка в создании формы, если последняя общая буква в правильном слове удвоена
    if(delLetters > 0 && !correct.isEmpty()&& fullCorrect[delLetters-1] == correct[0])
        return WRONG_CREATE;

    // Считать, что ошибка в выборе слова (слово другое), если остаток правильного длиннее максимально возможного формообразователя
    if(correct.length()>4)
        return WRONG_WORD;

    // Если остаток правильного соответствует возможным окончаниям формы
    if(cmpWithList(correct, endings)!= -1 || correct == "y" || (correct.isEmpty() && delLetters > 0))
    {
       // Если остаток неправильного возможным окончаниям формы
       if(cmpWithList(wrong, endings)!= -1 || wrong == "y")
           // Считать, что ошибка в выборе формообразователя
           return WRONG_FORMER;
       // Иначе
       else
           // Считать, что ошибка в создании формы
           return WRONG_CREATE;
    }
    // Иначе ошибка в выборе слова (слово другое)
    else
        return WRONG_WORD;
}

Mistake identifyMistake(QString correct, QString wrong)
{
    QList <QList <QStringList>> dictionaries ={exceptionNouns,exceptionAdjectives,
         exceptionAdverbs, irregularVerbs, pronouns}; // набор словарей для проверки
    int dictPos[2] = {-1,-1};                        // позиция слова в словаре
    // Если хоть одно из слов пустое
    if(correct.isEmpty() || wrong.isEmpty())
    {
        // Считать,что ошибки нет
        return NO_MISTAKE;
    }
    // Иначе eсли правильное слово есть в словаре
    else if(cmpWithDicts(correct,dictionaries, dictPos))
    {
        // Идентифицировать словарную ошибку
        QList<QString> dictLine = dictionaries[dictPos[0]][dictPos[1]];
        return identifyDictMistake(wrong,dictLine,correct);
    }
    // Иначе
    else
    {
        // Идентифицировать обычную ошибку
        return identifyUsualMistake(correct, wrong);
    }
}

QString formulateMistake(Mistake mistake)
{
    QString formMistake;
    if(mistake == WRONG_FORM)
        formMistake = "неправильно выбранная форма слова";
    else if(mistake == WRONG_WORD)
        formMistake = "слово отличается от эталона";
    else if(mistake == WRONG_CREATE)
        formMistake = "неправильно создана форма слова";
    else if(mistake == WRONG_EXCEPTION)
        formMistake = "неправильно создана форма-исключение";
    else if(mistake == WRONG_FORMER)
        formMistake = "неправильно выбранный формообразователь";
    else if(mistake == NO_MISTAKE)
        formMistake = "форма, как и эталон, является правильной";
    return formMistake;
}

void rearrangeNegatives(QString &str)
{
    //..Считать, что отрицание есть
    bool haveNeg = true;
    // Пока отрицание есть
    while(haveNeg)
    {
        // Если строка содержит can't
        if(str.contains("can\'t"))
            // Заменить на can not
            str.replace(str.indexOf("can\'t"), 5, "can not");
        // Иначе если строка содержит won't
        else if(str.contains("won\'t"))
            // Заменить на will not
            str.replace(str.indexOf("won\'t"), 5, "will not");
        // Иначе если строка содержит обычное сокращение
        else if(str.contains("n\'t"))
            // Заменить на not
            str.replace(str.indexOf("n\'t"), 3, " not");
        // Иначе
        else
            // Считать, что отрицания нет
            haveNeg = false;
    }
}

QStringList loadFile (QString filePath)
{
    QStringList list;
    if (!filePath.isEmpty()) // если имя файла задано
    {
         QFile file(filePath);
         // Открыть файл только для чтения
         if (file.open(QIODevice::ReadOnly) )
         {
            // Создать поток для данных
            QTextStream input( &file );
            QString data;
            // Получать данные из потока, пока они есть
            while (!input.atEnd())
            {
                data = input.readLine();
                list << data;
            }
            // Закрыть файл
            file.close();
         }
         else
             throw 0;
    }
    else
        throw 0;
    return list;
}

void saveToFile(QString filePath, QStringList text)
{
    // Если задан путь
    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        // Открыть файл только для записи
        if(file.open(QIODevice::WriteOnly))
        {
            // Создаем выходной поток
            QTextStream out(&file);
            QStringList::const_iterator iterator;
            if(!text.isEmpty())
            {
                // Для каждой строки сохраняемого текста
                for(iterator = text.constBegin(); iterator<text.constEnd()-1; iterator++)
                {
                    // Сохранить строку
                    out << *iterator;
                    out << "\n";
                }
                out << *iterator;
                //Закрыть файл
                file.close();
            }
        }
        else
            throw 1;
    }
    else
        throw 1;
}

