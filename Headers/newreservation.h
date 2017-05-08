#ifndef NEWRESERVATION_H
#define NEWRESERVATION_H

#include <QDialog>

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
    Ui::newReservation *ui;
};

#endif // NEWRESERVATION_H
