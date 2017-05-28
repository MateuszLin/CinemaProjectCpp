#include "Headers/modifyrezervation.h"
#include "ui_modifyrezervation.h"

modifyRezervation::modifyRezervation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyRezervation)
{
    ui->setupUi(this);
    ui->ticketLE->setValidator(new QIntValidator(1, 100, this));
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

void modifyRezervation::on_pushButton_clicked()
{
    if(ui->ticketLE->text().toInt() > 0)
    {
        QList<int> list;
        QList<int> &refList = list;
        int counter = 0;
        int &refCounter = counter;
        dB.whichSeatsBooked(refShowid, refList, refCounter, refrezId);
        dB.seatsCount(refhallid, refhallSeats);
        if(refhallSeats - refCounter < ui->ticketLE->text().toInt())
        {
            QMessageBox::warning(this, tr("Błąd!"), tr("Nie ma tylu wolnych miejsc!"));
        }
        else
        {
            {
                chooiceSeats* seats = new chooiceSeats();
                seats->setModal(true);
                seats->setText(ui->text->toPlainText());
                seats->setNameAndSurname("", "");
                seats->setShowID(showid);
                seats->setSeatsCount(ui->ticketLE->text().toInt());
                seats->setHallID(hallid);
                seats->setDbPointer(dB);
                seats->generateSeats(refhallSeats, refList);
                seats->setIsModifyRezerv(true);
                seats->setRezervId(refrezId);
                seats->exec();
                if(seats->getIsSeatsReserved()) this->close();
            }
        }

    }
    else
    {
        QMessageBox::warning(this, tr("Błąd!"), tr("Błędy w formularzu!"));
    }

}

void modifyRezervation::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Usuwanie","Czy na pewno chcesz usunac rezerwacje?\n",
                                   QMessageBox::Yes|QMessageBox::No);
     if(reply == QMessageBox::Yes)
     {
         dB.deleteRezervation(refrezId);
         this->close();
     }
}
