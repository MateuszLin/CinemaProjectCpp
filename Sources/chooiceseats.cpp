#include "Headers/chooiceseats.h"
#include "ui_chooiceseats.h"
#include "Headers/newreservation.h"
#include "QCheckBox"
#include "Headers/database.h"



chooiceSeats::chooiceSeats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooiceSeats)
{
    ui->setupUi(this);



//    sprawdzic czy jest cos zarezerwowane:
//        jesli tak zaznaczyc te miejsca w generateSeats


}

void chooiceSeats::setText(QString text)
{
    txt = text;
}

void chooiceSeats::setHallID(int hall)
{
    hallID = hall;
}

void chooiceSeats::setShowID(int showId)
{
    showID = showId;
}

void chooiceSeats::setSeatsCount(int count)
{
    tickets = count;
    ui->counterLabel->setText(QString::number(count));
    qDebug() << tickets << " count " << count;
}

void chooiceSeats::generateSeats()
{
    dB.seatsCount(refHall, refhallSeats);
    qDebug() << "w sali nr. " << refHall << " jest miejsc: " << refhallSeats;

    int rows = refhallSeats / 10;


    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < 10; col++) {
            //myDickIsBig
            QCheckBox* check = new QCheckBox();
            ui->gridL->addWidget(check, row, col);
            connect(check, SIGNAL(clicked(bool)), this, SLOT(check(bool)));

        }
    }

}

void chooiceSeats::setSeatsEnabled(bool state)
{
    for (int var = 0; var < ui->gridL->count() ; var++) {
        QCheckBox *box = qobject_cast<QCheckBox*>(ui->gridL->itemAt(var)->widget());
        if(!(box->isChecked()))
        {
            box->setEnabled(state);
        }
    }
}



void chooiceSeats::check(bool state)
{
    int counter = ui->counterLabel->text().toInt();
    if(!state)
    {
        if(counter == 0)
        {
            setSeatsEnabled(true);
        }
        counter++;
        ui->counterLabel->setText(QString::number(counter));
    }
    else
    {
        counter--;
        ui->counterLabel->setText(QString::number(counter));
        if(counter == 0)
        {
            setSeatsEnabled(false);
        }
        }
    }




chooiceSeats::~chooiceSeats()
{
    delete ui;
}

void chooiceSeats::on_pushButton_clicked()
{

}


