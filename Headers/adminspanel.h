#ifndef ADMINSPANEL_H
#define ADMINSPANEL_H

#include <QDialog>
#include "Headers/database.h"
#include "QMessageBox"


namespace Ui {
class adminsPanel;
}

class adminsPanel : public QDialog
{
    Q_OBJECT

public:
    explicit adminsPanel(QWidget *parent = 0);
    ~adminsPanel();

private slots:
    void on_addMovieBtn_clicked();

    void on_addShowBtn_clicked();

    void on_dateShowLE_textChanged(const QString &arg1);

    void on_timeShowLE_textChanged(const QString &arg1);

private:
    Ui::adminsPanel *ui;
    Database dB;
};

#endif // ADMINSPANEL_H
