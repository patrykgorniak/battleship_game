#ifndef GAMEHISTOGRAM_H
#define GAMEHISTOGRAM_H

#include <QHash>
#include <QFile>
#include <QTextStream>

class GameHistogram {

    public:

        GameHistogram();
        void readHistogram();
        void saveHistogram();
        int getHistogram(int pos);
        void setHistogram(int pos,int val);

    private:

        QHash<int,int> histogram;

};

#endif // GAMEHISTOGRAM_H

