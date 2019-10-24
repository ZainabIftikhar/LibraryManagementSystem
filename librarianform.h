#ifndef LIBRARIANFORM_H
#define LIBRARIANFORM_H

#include <QMainWindow>
#include "clerkform.h"

namespace Ui {
class librarianform;
}

class librarianform : public clerkform
{
    Q_OBJECT

public:
    explicit librarianform(QWidget *parent = 0);
    ~librarianform();

private slots:

    void on_searchTitlelib_clicked();
    void on_searchAuthorlib_clicked();
    void on_searchSubjectlib_clicked();
    void on_detailslib_clicked();
    void on_holdlib_clicked();
    void on_checkinlib_clicked();
    void on_checkoutlib_clicked();
    void on_renewlib_clicked();
    void on_finelib_clicked();
    void on_addlib_clicked();
    void on_updatelib_clicked();

    void on_additem_clicked();
    void on_deleteitem_clicked();
    void on_updateitem_clicked();
    void additem();
    void deleteitem();
    void edititem();
    void updateitem();
    void on_logoutlib_clicked();

private:
    Ui::librarianform *ui;
    QFormLayout *itemLayout;
    QFormLayout *itemEditLayout;
    QWidget *itemWidget;
    QWidget *itemEditWidget;
    vector <QLineEdit*> itemlines;
    void addsaveitem();
    void removesaveitem();
};

#endif // LIBRARIANFORM_H
