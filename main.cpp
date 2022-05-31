#include <QCoreApplication>

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
