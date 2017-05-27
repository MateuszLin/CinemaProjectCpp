#include "Headers/adminspanel.h"
#include "ui_adminspanel.h"

adminsPanel::adminsPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminsPanel)
{
    ui->setupUi(this);
}

adminsPanel::~adminsPanel()
{
    delete ui;
}
