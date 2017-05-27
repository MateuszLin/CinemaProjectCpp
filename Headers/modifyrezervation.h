#ifndef MODIFYREZERVATION_H
#define MODIFYREZERVATION_H

#include <QDialog>
#include <QtDebug>
#include "Headers/database.h"


namespace Ui {
class modifyRezervation;
}

class modifyRezervation : public QDialog
{
    Q_OBJECT

public:
    explicit modifyRezervation(QWidget *parent = 0);
    ~modifyRezervation();
    void setRezId(int &id);

private slots:
    void on_timeandDateCB_activated(int index);

private:
    Ui::modifyRezervation *ui;
    QString name, surname, seats, timeAndDate, movieName;
    QString &refName = name, &refSurname = surname, &refSeats = seats,
            &refTimeAndDate = timeAndDate, &refMovieName = movieName;

    int showid, hallid, rezId, movieId, ticket = 0;
    int &refShowid = showid, &refhallid = hallid, &refrezId = rezId, &refmovieId = movieId, &refticket = ticket;
    Database dB;
    void getRezervationInfo();
    void setTextBrowser();
    void setContent();
};

#endif // MODIFYREZERVATION_H
