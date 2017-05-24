#include "Headers/newreservation.h"
#include "ui_newreservation.h"



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
        else index++;


        dB.getDateTime(ui->dateCB, index);
    }
}


void newReservation::on_dateCB_activated(int index)
{
    if(!(ui->movieCB->itemText(index) == "Wybór filmu...") && !(ui->dateCB->itemText(index) == "Wybór daty i godziny..."))
    {
        if(ui->dateCB->itemText(0) == "Wybór daty i godziny..." )
        {
            ui->dateCB->removeItem(0);
            index--;
        }
        int idx = ui->movieCB->currentIndex() + 1;
        QString text = ui->dateCB->itemText(index);
        dB.setHallId(idx, refHall, text, refShow);

        QString hall = QString::number(hallID);
        qDebug() << hall;
        ui->infoBrowser->setText(ui->movieCB->itemText(idx - 1) + "\nTermin: " +  text + "\nSala nr." + hall);


    }
}

void newReservation::on_pushButton_clicked()
{
    if(ui->dateCB->currentText() != "Wybór daty i godziny..." && ui->movieCB->currentText() != "Wybór filmu..."
            && ui->nameLE->text().count() > 1 && ui->surnameLE->text().count() > 1
            && ui->ticketLE->text().toInt() > 0)
    {
        QList<int> list;
        QList<int> &refList = list;
        int counter = 0;
        int &refCounter = counter;
        dB.whichSeatsBooked(refShow, refList, refCounter);
        dB.seatsCount(refHall, refhallSeats);
        if(refhallSeats - refCounter < ui->ticketLE->text().toInt())
        {
            QMessageBox::warning(this, tr("Błąd!"), tr("Nie ma tylu wolnych miejsc!"));
        }
        else
        {
            chooiceSeats* seats = new chooiceSeats();
            seats->setModal(true);
            seats->setText(ui->infoBrowser->toPlainText());
            seats->setNameAndSurname(ui->nameLE->text(), ui->surnameLE->text());
            seats->setShowID(showId);
            seats->setSeatsCount(ui->ticketLE->text().toInt());
            seats->setHallID(hallID);
            seats->setDbPointer(dB);
            seats->generateSeats(refhallSeats, refList);
            seats->exec();
            if(seats->getIsSeatsReserved()) this->close();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Błąd!"), tr("Błędy w formularzu!"));

    }
}


