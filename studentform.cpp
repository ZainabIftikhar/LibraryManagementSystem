#include "interface.h"
#include "studentform.h"
#include "lms.h"
#include "ui_studentform.h"
#include "item.h"
#include "user.h"
#include "loan.h"
#include "hold.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>

extern lms *obj;
extern Filing *file;
extern interface *w;
extern user* active;

studentform::studentform(QWidget *parent) :QMainWindow(parent),ui(new Ui::studentform){
    ui->setupUi(this);
    this->setWindowTitle("Welcome Student");
    setsearch();
}

studentform::~studentform(){
    delete ui;
}

void studentform::setsearch() {
    label = new QLabel();
    line = new QLineEdit();
    tableWidget = new QTableWidget();

    Layout = new QHBoxLayout;
    Layout->addWidget(label);
    Layout->addWidget(line);

    createbutton();

    Widget = new QWidget;
    Widget->setLayout(Layout);
}

void studentform::createbutton() {
    button = new QPushButton("GO");
    Layout->addWidget(button);
}

void studentform::removebutton() {
    Layout->removeWidget(button);
    delete button;
}

void studentform::on_searchTitle_clicked(){
    removebutton();
    createbutton();

    label->setText("Enter the title of the book: ");

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(searchByTitle()));

    Widget->setWindowTitle("Search By Title");
    Widget->show();
}

void studentform::on_searchAuthor_clicked(){
    removebutton();
    createbutton();

    label->setText("Enter the author of the book: ");

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(searchByAuthor()));

    Widget->setWindowTitle("Search By Author");
    Widget->show();
}

void studentform::on_searchSubject_clicked(){
    removebutton();
    createbutton();

    label->setText("Enter the subject of the book: ");

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(searchBySubject()));

    Widget->setWindowTitle("Search By Subject");
    Widget->show();
}

void studentform::on_details_clicked(){
    displayuser(active);
}


void studentform::on_hold_clicked(){
    removebutton();
    createbutton();

    label->setText("Enter the id of the book: ");

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(holdPress()));

    Widget->setWindowTitle("Place on Hold");
    Widget->show();
}

void studentform::on_logout_clicked(){
    this->hide();

    delete label;
    delete line;
    delete Layout;
    delete Widget;

    w->show();
}

void studentform::searchByTitle() {
    QString Title = line->text();

    if(Title.isEmpty())
            QMessageBox::critical(this,"Search","Title is Required");

    else{
        Widget->close();
        vector <item *> ptr = obj->searchtitle(line->text().toLocal8Bit().constData());
        display(ptr);
    }
    line->setText(NULL);
}

void studentform::searchByAuthor() {
    QString Author = line->text();

    if(Author.isEmpty())
            QMessageBox::critical(this,"Search","Author Name is Required");

    else{
        Widget->close();
        vector <item *> ptr = obj->searchauthor(line->text().toLocal8Bit().constData());
        display(ptr);
    }
    line->setText(NULL);
}

void studentform::searchBySubject(){
    QString Subject = line->text();

    if(Subject.isEmpty())
            QMessageBox::critical(this,"Search","Subject is Required");

    else{
        Widget->close();
        vector<item *> ptr = obj->searchsubject(line->text().toLocal8Bit().constData());
        display(ptr);
    }
    line->setText(NULL);
}

void studentform::holdPress(){
    QString id = line->text();

    if(id.isEmpty())
            QMessageBox::critical(this,"Place on Hold","ID of the book is Required");

    else{
        Widget->close();
        item * ptr = obj->searchitem(line->text().toLocal8Bit().constData());
        QString message = QString::fromStdString(obj->placehold(ptr,active));
        QMessageBox::information(this,"Place on Hold",message);
    }
}

void studentform::display(vector <item*> ptr) {
    tableWidget->clear();
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->verticalHeader()->setVisible(true);

    if (ptr.size()!=0) {
        tableWidget->setWindowTitle("Results");
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);

        QStringList header;
        header << "Book ID" << "Title" << "Author" << "Subject";

        tableWidget->setHorizontalHeaderLabels(header);
        for (int c = 0; c < tableWidget->horizontalHeader()->count(); ++c){
            tableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
        }
        tableWidget->setShowGrid(true);

        for (int i = 0; i < ptr.size() ; i ++) {
        int currentRow = tableWidget->rowCount();
        tableWidget->setRowCount(currentRow + 1);

        tableWidget->setItem(currentRow, 0, new QTableWidgetItem(ptr[i]->getid().c_str()));
        tableWidget->setItem(currentRow, 1, new QTableWidgetItem(ptr[i]->gettitle().c_str()));
        tableWidget->setItem(currentRow, 2, new QTableWidgetItem(ptr[i]->getauthor().c_str()));
        tableWidget->setItem(currentRow, 3, new QTableWidgetItem(ptr[i]->getsubject().c_str()));
        }

        tableWidget->setFixedSize(500,200);
        tableWidget->show();
    }

    else {
        QMessageBox::information(this,"Search","No such book exists");
    }
    line->setText(NULL);
}

void studentform::displayuser(user * ptr) {
    tableWidget->clear();
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->verticalHeader()->setVisible(true);

    if (ptr != NULL) {
        tableWidget->setWindowTitle("Results");
        tableWidget->setRowCount(5);
        tableWidget->setColumnCount(1);
        QStringList header;

        header << "Roll No:" << "Name:" << "Address:" << "Telephone No:" << "Books Issued:";
        tableWidget->setVerticalHeaderLabels(header);
        tableWidget->horizontalHeader()->hide();

        for (int c = 0; c < tableWidget->horizontalHeader()->count(); ++c){
            tableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
            }

        tableWidget->setShowGrid(true);
        tableWidget->setItem(0, 0, new QTableWidgetItem(ptr->getid().c_str()));
        tableWidget->setItem(1, 0, new QTableWidgetItem(ptr->getname().c_str()));
        tableWidget->setItem(2, 0, new QTableWidgetItem(ptr->getaddress().c_str()));
        tableWidget->setItem(3, 0, new QTableWidgetItem(ptr->getphone().c_str()));

        vector <loan *> issued = ptr->booksissued();

        for (int i = 0; i < issued.size() ; i++) {
        int currentRow = tableWidget->rowCount();
        tableWidget->setRowCount(currentRow+1);
        header << " "; tableWidget->setVerticalHeaderLabels(header);
        tableWidget->setItem(currentRow-1, 0, new QTableWidgetItem(
                                 (issued[i]->getItem())->gettitle().c_str()));
        }

        tableWidget->setFixedSize(500,200);
        tableWidget->show();
        }

    else {
        QMessageBox::information(this,"Search","User not found");
        }
    line->setText(NULL);
}
