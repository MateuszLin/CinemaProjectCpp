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
    int newRezervationId();
    int newMovieID();
    int newMovieShowId();
    bool isAdminPassCorrect(QString &ref);
    void getAllMovies(QComboBox*);
    void getAllHalls(QComboBox*);
    void getDateTime(QComboBox*, int, bool modif = false);
    void setHallId(int movieId, int &hall, QString date, int &show);
    void seatsCount(int &hall, int &seatsCount);
    void addRezervation(int id, int show_id, int hall, QString name, QString surname, QString seats, int pass);
    void addMovieShow(int &id, int &movieId, int &hallId, QString timeDate);
    void whichSeatsBooked(int &show, QList<int> &seats, int &counter, int rezrvId = 0);
    void getModifyPass(QString &pass, int &refId);
    void getRezervationInfo(int &id, int &showid, int &hallid, QString &name, QString &surname, QString &seats);
    void getmovieShowInfo(int &id, int &movieid, QString &timeDate);
    void getMovieName(int &id, QString &name);
    void modifyRezervation(int &id, int &showid, int &hallid, QString seats);
    void deleteRezervation(int &id);

    void addMovie(QString &movieName, int &id);
};



#endif // DATABASE_H
