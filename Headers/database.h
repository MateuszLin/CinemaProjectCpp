#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QtSql>
#include <QtDebug>



using namespace std;

class Database
{
private:
    QSqlDatabase cinemaDB = QSqlDatabase::addDatabase("QSQLITE");

public:
    Database();

    void getAllMovies(QComboBox*);
    void getDateTime(QComboBox*, int);
    void setHallId(int movieId, int &hall, QString date, int &show);
    void seatsCount(int &hall, int &seatsCount);
    int newRezervationId();
    void addRezervation(int id, int show_id, int hall, QString name, QString surname, QString seats);
    void whichSeatsBooked(int &show, QList<int> &seats, int &counter);

};



#endif // DATABASE_H
