#include "Headers/newreservation.h"
#include "ui_newreservation.h"
#include "Headers/database.h"

using namespace std;

newReservation::newReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newReservation)
{
    ui->setupUi(this);

    ui->ticketLE->setValidator(new QIntValidator(1, 100, this));
    QRegExp expr("[a-zA-Z]+");
    QRegExpValidator *v = new QRegExpValidator(expr, this);
    ui->nameLE->setValidator(v);
    ui->surnameLE->setValidator(v);

    ui->movieCB->addItem("Wybór filmu...");
    dB.getAllMovies(ui->movieCB);


}


newReservation::~newReservation()
{
    delete ui;
}


void newReservation::on_movieCB_activated(int index)
{
    if(!(ui->movieCB->itemText(index) == "Wybór filmu..."))
    {
        if(ui->movieCB->itemText(0) == "Wybór filmu..." ) ui->movieCB->removeItem(0);


        dB.getDateTime(ui->dateCB, index);
    }
}

void newReservation::on_dateCB_activated(int index)
{
    if(!(ui->movieCB->itemText(index) == "Wybór daty i godziny..."))
    {
        if(ui->dateCB->itemText(0) == "Wybór daty i godziny..." ) ui->dateCB->removeItem(0);

    }
}
