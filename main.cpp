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
