#ifndef GAMEHISTOGRAM_H
#define GAMEHISTOGRAM_H

#include <QHash>
#include <QList>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <iostream>

using namespace std;

class GameHistogram {

    public:
        GameHistogram();
        GameHistogram(QString);
        void readHistogram();
        void saveHistogram();
        int getHistogram(int pos);
        void setHistogram(int pos,int val);
        void modifyHistogram(int pos);
        void checkValues();
        QList<int> generateSortedList();

    private:

        QMap<int,int> hist_sort;

        QHash<int,int> histogram;
        QHash<int,int> o_histogram;

        QString file_name;

};

#endif // GAMEHISTOGRAM_H

