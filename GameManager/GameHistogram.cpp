#include "GameHistogram.h"


int GameHistogram::getHistogram(int pos)
{
    return histogram.value(pos);
}

void GameHistogram::setHistogram(int pos, int val)
{
    histogram.insert(pos,val);
}

void GameHistogram::readHistogram()
{
    int counter = 0;
    QFile file("histogram.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

        QTextStream in(&file);
        while (!in.atEnd()) {
             QString line = in.readLine();
             histogram.insert(counter,line.toInt());
             counter++;
        }
}

void GameHistogram::saveHistogram()
{
    QFile file("histogram.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return;

    QTextStream out(&file);
    QHashIterator<int, int> i(histogram);
    while (i.hasNext()) {

         i.next();
         out << i.value() << endl;
     }

}
