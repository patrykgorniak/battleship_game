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
        GameHistogram(QString f_name, int b_size);
        virtual ~GameHistogram();
        void readHistogram();
        void saveHistogram();
        int getHistogram(int pos);
        void setHistogram(int pos,int val);
        void modifyHistogram(int pos);
        void checkValues();
        void clearHistogram();
        QList<int> generateSortedList();

    private:

        QMap<int,int> hist_sort;
        QHash<int,int> histogram;
        QHash<int,int> o_histogram;
        QString file_name;
        int board_size;

};

#endif // GAMEHISTOGRAM_H

