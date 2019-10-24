#ifndef CLERKFORM_H
#define CLERKFORM_H

#include <QMainWindow>
#include <QFormLayout>

#include "studentform.h"
namespace Ui {
class clerkform;
}

class clerkform : public studentform
{
    Q_OBJECT

public:
    explicit clerkform(QWidget *parent = 0);
    ~clerkform();

protected slots:
    void on_searchTitleclerk_clicked();
    void on_searchAuthorclerk_clicked();
    void on_searchSubjectclerk_clicked();
    void on_detailsclerk_clicked();
    void on_holdclerk_clicked();
    void on_checkin_clicked();
    void on_checkout_clicked();
    void on_renew_clicked();
    void on_fine_clicked();
    void on_add_clicked();
    void on_update_clicked();
    void on_logoutclerk_clicked();
    void checkin();
    void checkout();
    void renew();
    void add();
    void edit();
    void update();
    void fine();

protected:
    Ui::clerkform *ui;
    QLabel *label_2;
    QLineEdit *line_2;
    QLabel *result;
    QPushButton *save;
    void setmore();
    void removeform();
    void instantiateform();
    loan* gettheloan();
    void setclerks();
    void removesave();
    void addsave();
    QFormLayout *formLayout;
    QWidget *formWidget;
    vector <QLineEdit*> formlines;
};

#endif // CLERKFORM_H
