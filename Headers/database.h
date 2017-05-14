#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>


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
};

#endif // DATABASE_H
