#include "Headers/newreservation.h"
#include "ui_newreservation.h"

newReservation::newReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newReservation)
{
    ui->setupUi(this);
}

newReservation::~newReservation()
{
    delete ui;
}
