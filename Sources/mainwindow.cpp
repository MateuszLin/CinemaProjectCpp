#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    newReservation newres;
    newres.setModal(true);
    newres.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    pass = QInputDialog::getText(this, "Hasło", "Wprowadź hasło:");

    Database dB;
    dB.getModifyPass(refPass, refId);
    qDebug() << refId;
    if(id == 0)
    {
        QMessageBox msg;
        msg.setText("Hasło nieprawidłowe");
        msg.exec();
    }
    else
    {
        modifyRezervation modif;
        modif.setModal(true);
        modif.setRezId(refId);
        modif.exec();

    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString adminPass = QInputDialog::getText(this, "Hasło", "Wprowadź hasło dla administratora:");
    Database dB;
    QString &refadminPass = adminPass;
    if(dB.isAdminPassCorrect(refadminPass))
    {
        adminsPanel panel;
        panel.setModal(true);
        panel.exec();
    }
    else
    {
        QMessageBox box;
        box.setText("Hasło nieprawidłowe");
        box.exec();
    }

}
