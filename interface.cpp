#include "interface.h"
#include "ui_interface.h"
#include "user.h"
#include "lms.h"
#include "studentform.h"
#include "clerkform.h"
#include "librarianform.h"
#include <typeinfo>

using namespace std;

extern lms *obj;
user *active;

interface::interface(QWidget *parent) :QMainWindow(parent),ui(new Ui::interface){
    ui->setupUi(this);
}

interface::~interface(){
    delete ui;
}

bool interface::checkempty () {
    if (ui->id->text() == NULL)
         ui->label_4->setText("<font color='red'>*</font>");
    if (ui->pw->text() == NULL)
         ui->label_5->setText("<font color='red'>*</font>");
    if (ui->id->text() == NULL || ui->pw->text() == NULL)
        return false;

    return true;
}

void interface::on_login_clicked(){
    if (checkempty()) {
        active = obj->searchuser((ui->id->text()).toLocal8Bit().constData());
        if (active != NULL && active->matchpassword(ui->pw->text().toLocal8Bit().constData())) {
                this->hide();
                studentform * st;

                QString temp = typeid(*(active)).name();
                if (temp == "class student")
                        st = new studentform;
                else if (temp == "class clerk")
                        st = new clerkform;
                else if (temp == "class librarian")
                    st = new librarianform;
                st->show();
        }
        else {
            ui->error_3->setText("<font color='red'>Incorrect username or password!</font>");
        }
    }
}
