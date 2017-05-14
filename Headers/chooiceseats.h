#ifndef CHOOICESEATS_H
#define CHOOICESEATS_H

#include <QDialog>
#include "QListWidgetItem"
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
    void setSeatsCount(int count);
    void generateSeats();


    ~chooiceSeats();
private:
    void setSeatsEnabled(bool);

private slots:
    void on_pushButton_clicked();
    void check(bool);



private:
    Ui::chooiceSeats *ui;
    QString txt;
    int hallID;
    int &refHall = hallID;
    int tickets;
    int hallSeats;
    int &refhallSeats = hallSeats;
    int showID;
    Database &dB;

};

#endif // CHOOICESEATS_H
