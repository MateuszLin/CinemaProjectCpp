#ifndef NEWRESERVATION_H
#define NEWRESERVATION_H

#include "Headers/database.h"
#include "Headers/chooiceseats.h"
#include <QtSql>
#include <QtDebug>
#include <QMessageBox>

namespace Ui {
class newReservation;
}

class newReservation : public QDialog
{
    Q_OBJECT

public:
    explicit newReservation(QWidget *parent = 0);


    ~newReservation();

private:
      int hallID;
      int showId;
      int hallSeats;
      int &refHall = hallID, &refShow = showId,  &refhallSeats = hallSeats;


private slots:
    void on_movieCB_activated(int index);
    void on_dateCB_activated(int index);
    void on_pushButton_clicked();


private:
    Ui::newReservation *ui;
    Database dB;
};

#endif // NEWRESERVATION_H
