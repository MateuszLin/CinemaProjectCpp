#include "Headers/database.h"



Database::Database()
{
    cinemaDB.setDatabaseName("C:/Users/daron/Documents/RezerwacjaKino/rezervationDB.db");
}

void Database::getAllMovies(QComboBox *box)
{
    QSqlQuery qry;


    cinemaDB.open();
    qry.prepare("select * from movies order by movie_id asc");

    if(qry.exec())
    {
        QSqlRecord rec = qry.record();

        int nameCol = rec.indexOf("name");

        while(qry.next())
        {
             qDebug() << qry.value(nameCol).toString();
             box->addItem(qry.value(nameCol).toString());
        }
    }

    cinemaDB.close();
}

void Database::getDateTime(QComboBox *box, int index)
{

    box->clear();

    cinemaDB.open();
    qDebug() << cinemaDB.open() << " open db";
    QSqlQuery qry;
    qry.prepare("Select timeAndDate from movieShows where movie_id = (:index)");
    qry.bindValue(":index", index);


    if(qry.exec())
    {
        qDebug() << qry.first();
        if(!qry.first())
        {
             box->addItem("Brak seansów...");
        }
        else
        {
            box->addItem("Wybór daty i godziny...");
            QSqlRecord rec = qry.record();
            int dateCol = rec.indexOf("timeAndDate");


            box->addItem(qry.value(dateCol).toString());


            while(qry.next())
            {
                qDebug() << qry.value(dateCol).toString();
                box->addItem(qry.value(dateCol).toString());

            }

        }
    }


    cinemaDB.close();
}

void Database::setHallId(int movieId, int & hall, QString date, int &show)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select hall_id, id from movieShows where movie_id = (:movieId) and timeAndDate = (:date)");
    qry.bindValue(":movieId", movieId);
    qry.bindValue(":date", date);
    qDebug() << "movie id" << movieId;
    qDebug() << "date " << date;

    if(qry.exec())
    {
       if(qry.first())
       {
           QSqlRecord rec = qry.record();
           int hallCol = rec.indexOf("hall_id");
           int idCol = rec.indexOf("id");

           int id = qry.value(idCol).toInt();
           int hallid = qry.value(hallCol).toInt();
           qDebug() << "date " << hallid << " value " << qry.value(hallCol);
           qDebug() << "id " << id << " value " << qry.value(idCol);
           hall = hallid;
           show = id;
       }
    }
    cinemaDB.close();
}

void Database::seatsCount(int &hall, int &seatsCount)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select slots from cinemaHall where id_hall = (:hall)");
    qry.bindValue(":hall", hall);

    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int slotsCol = rec.indexOf("slots");
            int slotsHall = qry.value(slotsCol).toInt();
            seatsCount = slotsHall;
        }
    }

    cinemaDB.close();
}




