#include <iostream>
#include "lms.h"
#include "user.h"
#include "item.h"
#include "loan.h"
#include "hold.h"
#include "book.h"
#include "dvd.h"
#include "student.h"
#include <vector>
#include <string.h>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDate>
#include <QDebug>

extern Filing *file;

using namespace std;

lms::lms(){
}

vector <item*> lms::searchtitle(string title) {
    vector <item*> ret;

    for (int i = 0; i < items.size(); i++) {
        if (title == items[i]->gettitle()) {
            ret.push_back(items[i]);
        }
    }

    return ret;
}

vector <item *> lms::searchauthor(string author) {
    vector <item*> ret;

    for (int i = 0; i < items.size(); i++) {
        if (author == items[i]->getauthor()) {
            ret.push_back(items[i]);
        }
    }

    return ret;
}


vector <item *> lms::searchsubject(string subject) {
    vector <item*> ret;

    for (int i = 0; i < items.size(); i++) {
        if (subject == items[i]->getsubject()) {
            ret.push_back(items[i]);
        }
    }

    return ret;
}

void lms::additem(item * i) {
    items.push_back(i);
}

void lms::adduser(user * i) {
    users.push_back(i);
}

user * lms::searchuser(string id) {
    for (int i = 0; i < users.size(); i++) {
        if (id == users[i]->getid()) {
            return users[i];
        }
    }
    return NULL;
}


item * lms::searchitem(string id) {
    for (int i = 0; i < items.size(); i++) {
        if (id == items[i]->getid()) {
            return items[i];
        }
    }
    return NULL;
}

loan * lms::searchloan(item * i , user * u) {
    loan * temp = NULL;
    vector <loan *> issued = u->booksissued();
    for (int j = 0; j < issued.size(); j++)
        //books user have issued
        if (issued[j]->getItem()->getid() == i->getid()
                && issued[j]->getstatus() == "not returned") {
            temp = issued[j];
            return temp;
        }
    return temp;
}

hold * lms::searchhold(item* i ,user* u){
    hold * temp = NULL;
    vector <hold *> placedhold = u->bookshold();
    for (int j = 0; j < placedhold.size(); j++)
        //books user have issued
        if (placedhold[j]->getItem()->getid() == i->getid()
                && placedhold[j]->getstatus() == "not issued") {
            temp = placedhold[j];
            return temp;
        }
    return temp;
}

string lms::placehold(item * i, user * u){
    if (i == NULL || u == NULL)
        return ("Incorrect Combination!");

    string result = i->placeOnHold(u);
    return result;
}

string lms::checkIn(item * i , user * u){
    if (i == NULL || u == NULL)
        return ("Incorrect Combination!");

    string result = i->checkIn(u);
    return result;
}

string lms::checkOut(item *i, user *u){
    if (i == NULL || u == NULL)
        return ("Incorrect Combination!");

    string result = i->issue(u);
    return result;
}

string lms::renew(item *i, user * u) {
    if (i == NULL || u == NULL)
        return ("Incorrect Combination!");

    string result = i->renew(u);
    return result;
}

string lms::calculatefine(string id, QDate rdate){
    user * temp = searchuser(id);
    int fine = 0;
    if ( temp!= NULL ) {
        vector <loan*> issued = temp->booksissued();
        for (int i=0; i<issued.size(); i++){
            QDate idate = QDate::fromString(
                 QString::fromStdString(issued[i]->getdate()),"dd-MM-yyyy");
            int difference = idate.daysTo(rdate);

            if (difference > 14) {
                difference -= 14;
                fine += difference * 5;
            }

        }
        string s = to_string(fine);
        return ("Total Fine: " + s + " Fine paid!");
    }
    return ("User Not Found");
}

string lms::addnewuser(string id, string pw,string name, string address, string telephone) {
    user * newuser = new student(id,pw,name,address,telephone);
    adduser(newuser);
    file->save();
    return ("Borrower has been added");
}

string lms::edituser(string oldid,string id, string name, string address, string telephone){
    user * temp = searchuser(oldid);
    temp->setid(id);
    temp->setname(name);
    temp->setaddress(address);
    temp->settelephone(telephone);
    file->save();
    return ("User has been edited");
}

string lms::addnewitem(string type, string id, string title,string author, string subject, string status) {
    if (type == "Book"){
        item * newbook = new book(id,title,author,subject,status);
        additem(newbook);
    }
    else if (type == "DVD") {
        item * newdvd = new dvd(id,title,author,subject,status);
        additem(newdvd);
    }
    file->save();
    return ("Item has been added");
}

string lms::edititem(string oldid, string id, string title, string author, string subject) {
    item * temp = searchitem(oldid);
    temp->setid(id);
    temp->settitle(title);
    temp->setauthor(author);
    temp->setsubject(subject);
    file->save();
    return("Item has been edited");
}

string lms::deleteitem(string id) {
    item * temp = searchitem(id);
    if (temp == NULL)
            return ("Please enter a correct ID");

    if (temp->candelete()){
        for (int i = 0; i < items.size(); i++)
            if  (temp->getid() == items[i]->getid()) {
                vector<item *>::iterator nth = items.begin() + i;
                items.erase(nth);
                return ("Item has been deleted");
            }
    }

    return ("Item is currently on hold or loaned");
}
