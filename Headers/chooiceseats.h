#ifndef CHOOICESEATS_H
#define CHOOICESEATS_H

#include <QDialog>
#include "Headers/newreservation.h"
#include "QCheckBox"
#include "Headers/database.h"


namespace Ui {
class chooiceSeats;
}

class chooiceSeats : public QDialog
{
    Q_OBJECT

public:
    explicit chooiceSeats(QWidget *parent = 0);
    void setText(QString text);
    void setHallID(int hall);
    void setShowID(int showId);
    void setNameAndSurname(QString name, QString surname);
    void setSeatsCount(int count);
    void setDbPointer(Database base);
    void generateSeats(int &seats, QList<int> &refList);
    bool getIsSeatsReserved();
    void setIsModifyRezerv(bool);
    void setRezervId(int &ref);
    ~chooiceSeats();

private:
    void setSeatsEnabled(bool);
    QString rezervationSeats();
    Ui::chooiceSeats *ui;
    bool isSeatsReserved = false, isModifyRezerv = false;
    QString txt, name, surname;
    int hallID, tickets, showID, hallSeats, rezervId;
    int &refHall = hallID, &refhallSeats = hallSeats, &refRezervId = rezervId;
    Database *dB;

private slots:
    void on_pushButton_clicked();
    void check(bool);


};

#endif // CHOOICESEATS_H
