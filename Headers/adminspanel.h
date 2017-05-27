#ifndef ADMINSPANEL_H
#define ADMINSPANEL_H

#include <QDialog>

namespace Ui {
class adminsPanel;
}

class adminsPanel : public QDialog
{
    Q_OBJECT

public:
    explicit adminsPanel(QWidget *parent = 0);
    ~adminsPanel();

private:
    Ui::adminsPanel *ui;
};

#endif // ADMINSPANEL_H
