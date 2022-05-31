#include <QCoreApplication>
#include "functions.h"
#include "dictionaries.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
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

    QString fullWrong = wrong;                                  // копия неправильного слова
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
    if(fullCorrect[delLetters-1] == correct[0])
        return WRONG_CREATE;

    // Считать, что ошибка в выборе слова (слово другое), если остаток правильного длиннее максимально возможного формообразователя
    if(correct.length()>4)
        return WRONG_WORD;

    // Если остаток правильного соответствует возможным окончаниям формы
    if(cmpWithList(correct, endings)!= -1 || correct == "y" || correct.isEmpty())
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
    QList <QList <QStringList>> dictionaries ={exeptionNouns,exeptionAdjectives,
         exeptionAdverbs, irregularVerbs, pronouns}; // набор словарей для проверки
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
