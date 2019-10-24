#include "clerkform.h"
#include "studentform.h"
#include "ui_clerkform.h"

#include "lms.h"
#include "filing.h"
#include "interface.h"
#include "user.h"
#include "item.h"
#include "loan.h"
#include "QDebug"
#include <QDate>
#include "loan.h"
#include "student.h"
#include <QMessageBox>

extern lms *obj;
extern Filing *file;
extern interface *w;
extern user* active;

clerkform::clerkform(QWidget *parent) :studentform(parent),ui(new Ui::clerkform){
    ui->setupUi(this);
    this->setWindowTitle(" Welcome Clerk");

    setsearch();
    setclerks();
}

void clerkform::setclerks(){
    label_2 = new QLabel();
    line_2 = new QLineEdit();

    formLayout = new QFormLayout();

    formWidget = new QWidget();
    formWidget->setFixedSize(300,150);

    for (int i = 0 ; i < 4; i++)
        formlines.push_back(new QLineEdit());

    formWidget->setWindowTitle("Fill out the form");

    formLayout->addRow(tr(" Roll No:    "), formlines[0]);
    formLayout->addRow(tr(" Name:    "), formlines[1]);
    formLayout->addRow(tr(" Address:    "), formlines[2]);
    formLayout->addRow(tr(" Telephone:    "), formlines[3]);

    addsave();
    formWidget->setLayout(formLayout);
}

clerkform::~clerkform(){
    delete ui;
}

void clerkform::setmore() {
    Layout->addWidget(label_2);
    Layout->addWidget(line_2);
    Widget->setLayout(Layout);
}

void clerkform::removeform() {
    if (label_2!= NULL && line_2!= NULL) {
        Layout->removeWidget(label_2);
        Layout->removeWidget(line_2);
        delete label_2;
        delete line_2;
        label_2 = NULL;
        line_2 = NULL;
     }
}

void clerkform::on_searchTitleclerk_clicked(){
    removeform();
    on_searchTitle_clicked();
}

void clerkform::on_searchAuthorclerk_clicked(){
    removeform();
    on_searchAuthor_clicked();
}

void clerkform::on_searchSubjectclerk_clicked(){
    removeform();
    on_searchSubject_clicked();
}

void clerkform::on_detailsclerk_clicked(){
    removeform();
    on_details_clicked();
}

void clerkform::on_holdclerk_clicked(){
    removeform();
    on_hold_clicked();
}

void clerkform::instantiateform() {
    line->setText(NULL);
    label_2 = new QLabel;
    line_2 = new QLineEdit;

    setmore();
    removebutton();
    createbutton();

    label->setText("Enter the id of the book: ");
    label_2->setText("Enter the roll-no: ");
}

void clerkform::on_checkin_clicked(){
    removeform();
    instantiateform();

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(checkin()));
    Widget->setWindowTitle("Check in an item");
    Widget->show();

}

void clerkform::on_checkout_clicked(){
    removeform();
    instantiateform();

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(checkout()));
    Widget->setWindowTitle("Check out an item");
    Widget->show();
}

void clerkform::on_renew_clicked(){
    removeform();
    instantiateform();

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(renew()));
    Widget->setWindowTitle("Renew an item");
    Widget->show();
}

//return
void clerkform::checkin() {
    QString Itemname = line->text();
    QString Username = line_2->text();
    if(Itemname.isEmpty() || Username.isEmpty())
            QMessageBox::critical(this,"Check In","Please fill in the details");

    else {
        item * ptr = obj->searchitem(Itemname.toLocal8Bit().constData());
        user * current = obj->searchuser(Username.toLocal8Bit().constData());
        QString message = QString::fromStdString(obj->checkIn(ptr,current));
        QMessageBox::information(this,"Check In",message);
    }
}

//issue
void clerkform::checkout() {
    QString Itemname = line->text();
    QString Username = line_2->text();
    if(Itemname.isEmpty() || Username.isEmpty())
            QMessageBox::critical(this,"Check In","Please fill in the details");

    else {
        item * ptr = obj->searchitem(Itemname.toLocal8Bit().constData());
        user * current = obj->searchuser(Username.toLocal8Bit().constData());
        QString message = QString::fromStdString(obj->checkOut(ptr,current));
        QMessageBox::information(this,"Check Out",message);
    }
}

//re-issue
void clerkform::renew() {
    QString Itemname = line->text();
    QString Username = line_2->text();
    if(Itemname.isEmpty() || Username.isEmpty())
            QMessageBox::critical(this,"Check In","Please fill in the details");

    else {
        item * ptr = obj->searchitem(Itemname.toLocal8Bit().constData());
        user * current = obj->searchuser(Username.toLocal8Bit().constData());
        QString message = QString::fromStdString(obj->renew(ptr,current));
        QMessageBox::information(this,"Renew",message);
    }
}


void clerkform::on_fine_clicked(){
    removeform();
    removebutton();
    createbutton();

    label->setText("Enter the id of the user: ");

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(fine()));

    Widget->setWindowTitle("Enter User ID");
    Widget->show();
}

void clerkform::fine() {
    QString Username = line->text();
    if(Username.isEmpty())
            QMessageBox::critical(this,"Pay Fine","User is Required");

    else{
        Widget->close();
        QString message = QString::fromStdString(obj->calculatefine(Username.toLocal8Bit().constData(), QDate::currentDate()));
        QMessageBox::information(this,"Pay Fine",message);
    }
    line->setText(NULL);


}

void clerkform::removesave(){
    if (save!= NULL) {
        formLayout->removeWidget(save);
        delete save;
        save = NULL;
    }
}

void clerkform::addsave() {
    save = new QPushButton("Save");
    formLayout->addWidget(save);
}

void clerkform::on_add_clicked(){
    removeform();
    removesave();
    addsave();

    QObject::connect(save,SIGNAL(clicked()),this,SLOT(add()));
    formWidget->show();
}

void clerkform::on_update_clicked(){
    removeform();
    removebutton();
    createbutton();

    label->setText("Enter the roll-no: ");
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(edit()));

    Widget->setWindowTitle("Edit the borrower");
    Widget->show();
}

void clerkform::add() {
    QString id = formlines[0]->text();
    QString name = formlines[1]->text();
    QString address = formlines[2]->text();
    QString telephone = formlines[3]->text();

    if (id.isEmpty() || name.isEmpty() || address.isEmpty() || telephone.isEmpty())
        QMessageBox::critical(this,"Add User","All fields are Required");
    else {
        formWidget->hide();
        QString message = QString::fromStdString(obj->addnewuser(id.toStdString(),
                          "12345",name.toStdString(),address.toStdString(),
                           telephone.toStdString()));
        QMessageBox::information(this,"Add User",message);
    }
}

void clerkform::edit() {
    Widget->hide();
    removesave();
    addsave();

    user * u = obj->searchuser(line->text().toLocal8Bit().constBegin());
    if (u!= NULL) {
        formlines[0]->setText(u->getid().c_str());
        formlines[1]->setText(u->getname().c_str());
        formlines[2]->setText(u->getaddress().c_str());
        formlines[3]->setText(u->getphone().c_str());
        QObject::connect(save,SIGNAL(clicked()),this,SLOT(update()));
        formWidget->show();
    }

    else {
        QMessageBox::information(this,"Edit User","User not found!");
    }
}

void clerkform::update() {
    QString id = formlines[0]->text();
    QString name = formlines[1]->text();
    QString address = formlines[2]->text();
    QString telephone = formlines[3]->text();

    if (id.isEmpty() || name.isEmpty() || address.isEmpty() || telephone.isEmpty())
        QMessageBox::critical(this,"Edit User","All fields are Required");
    else {
        formWidget->hide();
        QString message = QString::fromStdString(obj->edituser(
                          line->text().toLocal8Bit().constData(),
                          id.toStdString(),
                          name.toStdString(),address.toStdString(),
                          telephone.toStdString()));
        QMessageBox::information(this,"Edit User",message);
    }
}

void clerkform::on_logoutclerk_clicked(){
    for (int i = 0; i < 4; i++) {
        delete formlines[i];
        formlines[i] = NULL;
    }
    delete save;
    save = NULL;
    delete formLayout;
    formLayout = NULL;
    delete formWidget;
    formWidget = NULL;
    delete label_2;
    label_2 = NULL;
    delete line_2;
    line_2 = NULL;
    delete result;
    result = NULL;
    on_logout_clicked();
}
