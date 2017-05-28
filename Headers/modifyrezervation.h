#ifndef MODIFYREZERVATION_H
#define MODIFYREZERVATION_H

#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include "Headers/database.h"
#include "Headers/chooiceseats.h"

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::modifyRezervation *ui;
    QString name, surname, seats, timeAndDate, movieName;
    QString &refName = name, &refSurname = surname, &refSeats = seats,
            &refTimeAndDate = timeAndDate, &refMovieName = movieName;

    int showid, hallid, hallSeats, rezId, movieId, ticket = 0;
    int &refShowid = showid, &refhallid = hallid, &refrezId = rezId, &refmovieId = movieId,
        &refticket = ticket, refhallSeats = hallSeats;
    Database dB;
    void getRezervationInfo();
    void setTextBrowser();
    void setContent();
};

#endif // MODIFYREZERVATION_H
