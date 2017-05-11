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
    index++;
    QSqlQuery qry;
    qry.prepare("Select * from movieShows where movie_id = (:index)");
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


