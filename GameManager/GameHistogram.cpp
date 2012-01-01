#include "GameHistogram.h"

//!  Domyślny konstruktor klasy GameHistrogram
/*!
*/
GameHistogram::GameHistogram()
{
    board_size=100;
    for(int i=0;i<board_size;i++)
    {
        histogram.insert(i,0);
    }
    file_name="histogram.txt";
}

//! Konstruktor parametrowy klasy GameHistrogram
/*!
      \param f_name nazwa pliku z histogramem
      \param b_size rozmiar planszy gry
      \return The test results
      \sa GameHistogram(), ~GameHistogram()
*/
GameHistogram::GameHistogram(QString f_name, int b_size)
{
    board_size = b_size;
    for(int i=0;i<board_size;i++)
    {
        histogram.insert(i,0);
    }
    file_name=f_name;
}
//!  Destruktor klasy GameHistrogram
/*!
*/
GameHistogram::~GameHistogram()
{
    this->clearHistogram();
}
//!  Funkcja usuwająca histogram z pamięci
/*!
     \sa ~GameHistogram()
*/
void GameHistogram::clearHistogram()
{
    histogram.clear();
    o_histogram.clear();
    hist_sort.clear();
}
//! Dostęp do wartości histogramu
/*!
      \param pos pozycja w histogramie
      \return wartość histogramu na określonej pozycji
      \sa setHistogram()
*/
int GameHistogram::getHistogram(int pos)
{
    return histogram.value(pos);
}
//! Dostęp do wartości histogramu
/*!
      \param pos pozycja w histogramie
      \param val nowa wartość
      \sa getHistogram()
*/
void GameHistogram::setHistogram(int pos, int val)
{
    if(val>15) val=15;
    histogram.insert(pos,val);
}
//! Modyfikacja wag w histogramie
/*!
      Po trafieniu wartość danego pola zwiększana jest o 3. Wartość max. 15
      \param pos pozycja w histogramie
      \sa checkValues()
*/
void GameHistogram::modifyHistogram(int pos)
{
    int val = histogram.value(pos);
    if(val>=15) {
         histogram.insert(pos,(15));
    }
    histogram.insert(pos,(val+3));
}
//! Sprawdzanie zmian w histogramie
/*!
      Po zakończeniu gry na podstawie kopii histogramu sprawdzane są zmiany w celu obniżenia wagi pól nietrafionych.
      \sa modifyHistogram()
*/
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
//! Wczytanie histogramu z pliku
/*!
      Wczytanie danych z pliku oraz utworzenie kopii histogramu w celu późniejszego śledzenia zmian
      \sa saveHistogram(), checkValues()
*/
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
//! Zapisanie histogramu do pliku
/*!
    \sa readHistogram(), clearHistogram()
*/
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
//! Utworzenie listy wg rosnących wag pól
/*!
    /return lista uporządkowana wg rosnących wag pól
*/
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
