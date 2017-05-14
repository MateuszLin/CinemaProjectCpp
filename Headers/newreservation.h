#ifndef NEWRESERVATION_H
#define NEWRESERVATION_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "Headers/database.h"

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

      int &refHall = hallID;
      int &refShow = showId;


private slots:
    void on_movieCB_activated(int index);
    void on_dateCB_activated(int index);
    void on_pushButton_clicked();


private:
    Ui::newReservation *ui;
    Database dB;
};

#endif // NEWRESERVATION_H
