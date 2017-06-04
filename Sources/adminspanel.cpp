#include "Headers/adminspanel.h"
#include "ui_adminspanel.h"

adminsPanel::adminsPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminsPanel)
{
    ui->setupUi(this);
    QRegExp exprDate("[0-3][0-9]-[01][0-9]-[2][0-9][0-9][0-9]");
    QRegExpValidator *v = new QRegExpValidator(exprDate, this);

    QRegExp exprTime("[0-2][0-9]:[0-5][0-9]");
    QRegExpValidator *v2 = new QRegExpValidator(exprTime, this);
    ui->dateShowLE->setValidator(v);
    ui->timeShowLE->setValidator(v2);

    dB.getAllMovies(ui->movieCB);
    dB.getAllHalls(ui->halliDCB);
}

adminsPanel::~adminsPanel()
{
    delete ui;
}

void adminsPanel::on_addMovieBtn_clicked()
{
    QString name = ui->movieNameLE->text();

    if(name.length() > 1)
    {
        int id = dB.newMovieID();
        int &refId = id;
        QString &refName = name;
        dB.addMovie(refName, refId);
        ui->movieCB->clear();
        ui->movieNameLE->clear();
        dB.getAllMovies(ui->movieCB);
        QMessageBox::information(this, tr("Sukces"), tr("Film został dodany do bazy"));

    }
    else
    {
        QMessageBox::warning(this, tr("Błąd!"), tr("Wprowadź poprawną nazwę!"));
    }

}

void adminsPanel::on_addShowBtn_clicked()
{
    QString time = ui->timeShowLE->text();
    QString date = ui->dateShowLE->text();
    int movieID = ui->movieCB->currentIndex() + 1;
    int hallID = ui->halliDCB->currentIndex() + 1;

    if(time.length() == 5 && date.length() == 10)
    {
        int id = dB.newMovieShowId();
        qDebug() << " time " << time << " date " << date << " sala nr " << hallID << " id " << id << " id m " << movieID;
        int &refHall = hallID, &refID = id, &refMovieID = movieID;
        dB.addMovieShow(refID, refMovieID, refHall, date + " " + time);
        QMessageBox::information(this, tr("Sukces"), tr("Dodano seans do bazy"));
    }
    else
    {
        QMessageBox::warning(this, tr("Błąd!"), tr("Błędy w formularzu!"));
    }
}


void adminsPanel::on_dateShowLE_textChanged(const QString &arg1)
{
    switch (arg1.length()) {
    case 2:
    case 5:
        ui->dateShowLE->clear();
        ui->dateShowLE->setText(arg1 + "-");
    default:
        break;
    }
}


void adminsPanel::on_timeShowLE_textChanged(const QString &arg1)
{
    if(arg1.length() == 2)
    {
        ui->timeShowLE->clear();
        ui->timeShowLE->setText(arg1 + ":");
    }
}
