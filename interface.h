#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    bool checkempty();
    ~interface();

private slots:
    void on_login_clicked();

private:
    Ui::interface *ui;
};

#endif // INTERFACE_H
