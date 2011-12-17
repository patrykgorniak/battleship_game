#include "GameHistogram.h"


GameHistogram::GameHistogram()
{
    board_size=100;
    for(int i=0;i<board_size;i++)
    {
        histogram.insert(i,0);
    }
    file_name="histogram.txt";
}

GameHistogram::GameHistogram(QString f_name, int b_size)
{
    board_size = b_size;
    for(int i=0;i<board_size;i++)
    {
        histogram.insert(i,0);
    }
    file_name=f_name;
}

GameHistogram::~GameHistogram()
{
    this->clearHistogram();
}

void GameHistogram::clearHistogram()
{
    histogram.clear();
    o_histogram.clear();
    hist_sort.clear();
}

int GameHistogram::getHistogram(int pos)
{
    return histogram.value(pos);
}

void GameHistogram::setHistogram(int pos, int val)
{
    if(val>15) val=15;
    histogram.insert(pos,val);
}

void GameHistogram::modifyHistogram(int pos)
{
    int val = histogram.value(pos);
    if(val>=15) {
         histogram.insert(pos,(15));
    }
    histogram.insert(pos,(val+3));
}

void GameHistogram::checkValues()
{
    int new_v,prev_v=0;
    for(int i=0;i<100;i++)
    {
        new_v = histogram.value(i);
        prev_v = o_histogram.value(i);

        if(new_v<=prev_v)
        {
            if(new_v-1>0)
            {
                histogram.insert(i,new_v-1);
            }
            else
            {
                histogram.insert(i,0);
            }
        }
    }
}

void GameHistogram::readHistogram()
{
    int counter = 0;
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        for(int i=0;i<board_size;i++)
        {
            histogram.insert(i,0);
        }
        this->saveHistogram();
     }
     else {
            QTextStream in(&file);
            while (!in.atEnd()) {
                 QString line = in.readLine();
                 histogram.insert(counter,line.toInt());
                 o_histogram.insert(counter,line.toInt());
                 counter++;
            }
        }
     file.close();
}

void GameHistogram::saveHistogram()
{
    this->checkValues();
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return;

    QTextStream out(&file);
    QHashIterator<int, int> i(histogram);
    while (i.hasNext()) {

         i.next();
         out << i.value() << endl;
     }
    this->clearHistogram();
    file.close();

}

QList<int> GameHistogram::generateSortedList()
{
    QList<int> sPos;

    QHashIterator<int, int> i(histogram);
    while (i.hasNext()) {

         i.next();
         hist_sort.insertMulti(i.value(),i.key());
    }

    QMapIterator<int, int> j(hist_sort);
    while (j.hasNext()) {
        j.next();
        sPos.push_back(j.value());
    }
    return sPos;
}
