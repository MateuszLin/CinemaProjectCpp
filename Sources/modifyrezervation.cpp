#include "Headers/modifyrezervation.h"
#include "ui_modifyrezervation.h"

modifyRezervation::modifyRezervation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyRezervation)
{
    ui->setupUi(this);
    ui->ticketLE->setValidator(new QIntValidator(1, 100, this));
    //id rez
    //show_id
    //hall_id
    //name
    //surname
    //seats


}

modifyRezervation::~modifyRezervation()
{
    delete ui;
}

void modifyRezervation::setRezId(int &id)
{
    rezId = id;
    getRezervationInfo();
    setContent();
    setTextBrowser();

}

void modifyRezervation::getRezervationInfo()
{
    dB.getRezervationInfo(refrezId, refShowid, refhallid, refName, refSurname, refSeats);
    dB.getmovieShowInfo(refShowid, refmovieId, refTimeAndDate);
    dB.getMovieName(refmovieId, refMovieName);
    dB.getDateTime(ui->timeandDateCB, movieId, true);


}

void modifyRezervation::setTextBrowser()
{
    QString str = name + " " + surname + "\n" + movieName +"\nSala nr." + QString::number(hallid) +
            "\nTermin: " + ui->timeandDateCB->currentText();
    ui->text->setText(str);

}

void modifyRezervation::setContent()
{
     ui->movieNameLE->setText(movieName);
     int index = 0;
     while (index <= ui->timeandDateCB->count())
     {

         if(ui->timeandDateCB->itemText(index) == timeAndDate)
         {
             ui->timeandDateCB->setCurrentIndex(index);
             break;
         }

         index++;
     }

     for(int i = 0; i < seats.length(); i++)
     {
         if(seats[i] == ';') ticket++;
     }

     ui->ticketLE->setText(QString::number(ticket));

}

void modifyRezervation::on_timeandDateCB_activated(int index)
{
    dB.setHallId(movieId, refhallid, ui->timeandDateCB->itemText(index), refShowid);
    setTextBrowser();
}
