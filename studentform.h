#ifndef STUDENTFORM_H
#define STUDENTFORM_H
#include "item.h"
#include "user.h"
#include "hold.h"
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidget>


namespace Ui {
class studentform;
}

class studentform : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentform(QWidget *parent = 0);
    ~studentform();
    void display(vector <item*> ptr);
    void displayuser(user * ptr);

protected slots:
    void on_searchTitle_clicked();
    void on_searchAuthor_clicked();
    void on_searchSubject_clicked();
    void on_details_clicked();
    void on_logout_clicked();
    void on_hold_clicked();
    void searchByTitle();
    void searchByAuthor();
    void searchBySubject();
    void holdPress();

protected:
    Ui::studentform *ui;
    QLabel *label;
    QLineEdit *line;
    QPushButton *button;
    QHBoxLayout *Layout;
    QWidget *Widget;
    QTableWidget *tableWidget;
    void setsearch();
    void createbutton();
    void removebutton();
};

#endif // STUDENTFORM_H
