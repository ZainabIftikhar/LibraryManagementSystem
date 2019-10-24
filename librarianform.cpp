#include "librarianform.h"
#include "clerkform.h"
#include "ui_librarianform.h"

#include "user.h"
#include "item.h"
#include "book.h"
#include "dvd.h"
#include "lms.h"
#include "filing.h"
#include <QDebug>
#include <QMessageBox>

extern lms *obj;
extern Filing *file;

librarianform::librarianform(QWidget *parent) :clerkform(parent),ui(new Ui::librarianform){
    ui->setupUi(this);
    itemLayout = new QFormLayout();
    itemWidget = new QWidget();
    itemWidget->setFixedSize(300,200);
    for (int i = 0 ; i < 5; i++)
        itemlines.push_back(new QLineEdit());
    itemWidget->setWindowTitle("Fill out the form");
    itemLayout->addRow(tr(" Item Type:    "), itemlines[0]);
    itemLayout->addRow(tr(" Item ID:    "), itemlines[1]);
    itemLayout->addRow(tr(" Item Name:    "), itemlines[2]);
    itemLayout->addRow(tr(" Item Author:    "), itemlines[3]);
    itemLayout->addRow(tr(" Item Subject:    "), itemlines[4]);
    addsaveitem();
    itemWidget->setLayout(itemLayout);
}

librarianform::~librarianform(){
    delete ui;
}

void librarianform::on_searchTitlelib_clicked(){
    on_searchTitleclerk_clicked();
}

void librarianform::on_searchAuthorlib_clicked(){
    on_searchAuthorclerk_clicked();
}

void librarianform::on_searchSubjectlib_clicked(){
    on_searchSubjectclerk_clicked();
}

void librarianform::on_detailslib_clicked(){
    on_detailsclerk_clicked();
}

void librarianform::on_holdlib_clicked(){
   on_holdclerk_clicked();
}

void librarianform::on_checkinlib_clicked(){
    on_checkin_clicked();
}

void librarianform::on_checkoutlib_clicked(){
    on_checkout_clicked();
}

void librarianform::on_renewlib_clicked(){
    on_renew_clicked();
}

void librarianform::on_finelib_clicked(){
    on_fine_clicked();
}

void librarianform::on_addlib_clicked(){
    on_add_clicked();
}

void librarianform::on_updatelib_clicked(){
    on_update_clicked();
}

void librarianform::removesaveitem(){
    itemLayout->removeWidget(save);
    delete save;
}

void librarianform::addsaveitem() {
    save = new QPushButton("Save");
    itemLayout->addWidget(save);
}

void librarianform::on_additem_clicked(){
    removesaveitem();
    addsaveitem();
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(additem()));
    itemWidget->show();
}

void librarianform::on_deleteitem_clicked(){
    removebutton();
    createbutton();
    label->setText("Enter the id of the item: ");
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(deleteitem()));
    Widget->setWindowTitle("Delete the item");
    Widget->show();
}

void librarianform::on_updateitem_clicked(){
    removebutton();
    createbutton();
    label->setText("Enter the item-no: ");
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(edititem()));
    Widget->setWindowTitle("Edit the item");
    Widget->show();
}


void librarianform::additem() {
    QString type = itemlines[0]->text();
    QString id = itemlines[1]->text();
    QString title = itemlines[2]->text();
    QString author = itemlines[3]->text();
    QString subject = itemlines[4]->text();

    if (type.isEmpty() || id.isEmpty() || title.isEmpty() || author.isEmpty() || subject.isEmpty())
        QMessageBox::critical(this,"Add Item","All fields are Required");
    else {
        itemWidget->hide();
        QString message = QString::fromStdString( obj->addnewitem(type.toStdString(),
                                             id.toStdString(),title.toStdString(),
                                             author.toStdString(),subject.toStdString(),
                                             "available"));
        QMessageBox::information(this,"Add Item",message);
    }
}

void librarianform::deleteitem() {
    QString Delete = line->text();
    if(Delete.isEmpty())
            QMessageBox::critical(this,"Delete","Item ID is Required");

    else{
        Widget->hide();
        QString message = QString::fromStdString(obj->deleteitem(Delete.toLocal8Bit().constData()));
        QMessageBox::information(this,"Delete Item",message);
    }
}

void librarianform::edititem() {
    Widget->hide();
    removesaveitem();
    addsaveitem();

    item * i = obj->searchitem(line->text().toLocal8Bit().constBegin());
    if (i!= NULL) {
        itemlines[1]->setText(i->getid().c_str());
        itemlines[2]->setText(i->gettitle().c_str());
        itemlines[3]->setText(i->getauthor().c_str());
        itemlines[4]->setText(i->getsubject().c_str());
        QObject::connect(save,SIGNAL(clicked()),this,SLOT(updateitem()));
        itemWidget->show();
    }
    else {
         QMessageBox::information(this,"Edit Item","Item not found!");
    }
}

void librarianform::updateitem() {
    QString type = itemlines[0]->text();
    QString id = itemlines[1]->text();
    QString title = itemlines[2]->text();
    QString author = itemlines[3]->text();
    QString subject = itemlines[4]->text();

    if (type.isEmpty() || id.isEmpty() || title.isEmpty() || author.isEmpty() || subject.isEmpty())
        QMessageBox::critical(this,"Add Item","All fields are Required");
    else {
        itemWidget->hide();
        QString message = QString::fromStdString(obj->edititem(line->text().toLocal8Bit().constData(),
                                             id.toStdString(),title.toStdString(),
                                             author.toStdString(),subject.toStdString()));
        QMessageBox::information(this,"Add Item",message);
    }
}

void librarianform::on_logoutlib_clicked(){
    this->close();
    on_logout_clicked();
}
