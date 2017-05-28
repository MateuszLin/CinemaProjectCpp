#include "Headers/database.h"



Database::Database()
{
    cinemaDB.setDatabaseName("C:/Users/daron/Documents/C++/RezerwacjaKino/rezervationDB.db");
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

void Database::getDateTime(QComboBox *box, int index, bool modif)
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
            if(!modif) box->addItem("Wybór daty i godziny...");

            QSqlRecord rec = qry.record();
            int dateCol = rec.indexOf("timeAndDate");


            box->addItem(qry.value(dateCol).toString());


            while(qry.next())
            {
                //qDebug() << qry.value(dateCol).toString();
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

int Database::newRezervationId()
{
    int count = 0;
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select count(rezervation_id) from rezervation");
    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int idCol = rec.indexOf("count(rezervation_id)");
            count = qry.value(idCol).toInt();
        }
    }
    \
    cinemaDB.close();
    count++;

    return count;

}

void Database::addRezervation(int id, int show_id, int hall, QString name, QString surname, QString seats)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Insert into rezervation (rezervation_id, show_id, hall_id, name, surname, seats) "
                "values ((:id), (:show), (:hall), (:name), (:surname), (:seats))");
    qry.bindValue(":id", id);
    qry.bindValue(":show", show_id);
    qry.bindValue(":hall", hall);
    qry.bindValue(":name", name);
    qry.bindValue(":surname", surname);
    qry.bindValue(":seats", seats);

    qry.exec();
    cinemaDB.commit();
    qDebug() << "dodano";
    cinemaDB.close();


}

void Database::whichSeatsBooked(int &show, QList<int> &seats, int &counter,  int rezrvId)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select seats, rezervation_id from rezervation where show_id = (:show)");
    qry.bindValue(":show", show);
    qDebug() << "show " << show;

    QString seatsS = "";
    counter = 0;

    if(qry.exec())
    {
        QSqlRecord rec = qry.record();
        int seatsCol = rec.indexOf("seats");
        int rezerIdCol = rec.indexOf("rezervation_id");

        while(qry.next())
        {
            int temp = qry.value(rezerIdCol).toInt();
            if(temp != rezrvId) seatsS += qry.value(seatsCol).toString();
        }
    }

    qDebug() << "string seats " << seatsS;
    QStringList split = seatsS.split(";");
    for (int var = 0; var < split.length() - 1; ++var) {
        qDebug() << "split " << split[var];
        seats.append(split[var].toInt());
        counter++;
    }

    foreach (int var, seats) {
        qDebug() << "int " << var;

    }

    cinemaDB.close();

}

void Database::getModifyPass(QString &pass, int &id)
{
    cinemaDB.open();

    QSqlQuery qry;
    qry.prepare("Select rezervation_id from rezervation where pass = (:pass)");
    qry.bindValue(":pass", pass);

    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int colId = rec.indexOf("rezervation_id");
            id = qry.value(colId).toInt();
        }
        else
        {
            id = 0;
        }
    }
    cinemaDB.close();


}

void Database::getRezervationInfo(int &id, int &showid, int &hallid, QString &name, QString &surname, QString &seats)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select * from rezervation where rezervation_id = (:id)");
    qry.bindValue(":id", id);

    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int showCol = rec.indexOf("show_id");
            int hallCol = rec.indexOf("hall_id");
            int nameCol = rec.indexOf("name");
            int surnameCol = rec.indexOf("surname");
            int seatsCol = rec.indexOf("seats");

            showid = qry.value(showCol).toInt();
            hallid = qry.value(hallCol).toInt();
            name = qry.value(nameCol).toString();
            surname = qry.value(surnameCol).toString();
            seats = qry.value(seatsCol).toString();

        }
    }
    cinemaDB.close();

}

void Database::getmovieShowInfo(int &id, int &movieid, QString &timeDate)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select * from movieShows where id = (:id)");
    qry.bindValue(":id", id);


    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int movieIdCol = rec.indexOf("movie_id");
            int timeDateCol = rec.indexOf("timeAndDate");
            timeDate = qry.value(timeDateCol).toString();
            movieid = qry.value(movieIdCol).toInt();
        }
    }
    cinemaDB.close();
}

void Database::getMovieName(int &id, QString &name)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("Select name from movies where movie_id = (:id)");
    qry.bindValue(":id", id);


    if(qry.exec())
    {
        if(qry.first())
        {
            QSqlRecord rec = qry.record();
            int nameCol = rec.indexOf("name");
            name = qry.value(nameCol).toString();
        }
    }

    cinemaDB.close();
}

void Database::modifyRezervation(int &id, int &showid, int &hallid, QString seats)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("UPDATE rezervation SET show_id = (:showid), "
                "hall_id = (:hallid), "
                "seats = (:seats) "
                "where rezervation_id = (:id)");
    qry.bindValue(":showid", showid);
    qry.bindValue(":hallid", hallid);
    qry.bindValue(":seats", seats);
    qry.bindValue(":id", id);

    qry.exec();
    cinemaDB.commit();
    cinemaDB.close();
}

void Database::deleteRezervation(int &id)
{
    cinemaDB.open();
    QSqlQuery qry;
    qry.prepare("DELETE FROM rezervation WHERE rezervation_id = (:id)");
    qry.bindValue(":id", id);

    qry.exec();
    cinemaDB.commit();
    cinemaDB.close();
}




