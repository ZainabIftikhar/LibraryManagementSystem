#include "item.h"
#include "hold.h"
#include "loan.h"
#include "state.h"
#include "available.h"
#include "issued.h"
#include "referenced.h"
#include "onhold.h"
#include "filing.h"
#include <iostream>
#include <QDebug>
extern Filing* file;
extern state * aObj;
extern state * iObj;
extern state * hObj;
extern state * rObj;

using namespace std;

item::item(){
}

item::item(string id,string title, string author, string subject,string status) {
    this->id = id;
    settitle(title);
    setauthor(author);
    setsubject(subject);
    if (status == "available")
            st = aObj;
    else if (status == "issued")
            st = iObj;
    else if (status == "onhold")
            st = hObj;
    else if (status == "referenced")
            st = rObj;
}

void item::addloan(loan*l){
    loans.push_back(l);
}

void item::addHold(hold*l){
    holds.push_back(l);
}

string item::getid() {
    return id;
}

string item::gettitle() {
    return title;
}

string item::getauthor() {
    return author;
}

string item::getsubject() {
    return subject;
}

void item::setid(string id) {
    this->id = id;
}

void item::settitle(string title) {
    this->title = title;
}

void item::setauthor(string author) {
    this->author = author;
}

void item::setsubject(string subject) {
    this->subject = subject;
}

vector <loan*> item::haveissued() {
    vector <loan*> temp;

    for (int i = 0; i < loans.size(); i++) {
        if ((loans[i]->getstatus()) == "not returned")
            temp.push_back(loans[i]);
    }

    return temp;
}

vector <hold*>item::haveholded() {
    vector <hold*> temp;
    for (int i = 0; i < holds.size(); i++) {
        if (holds[i]->getstatus() == "not issued")
            temp.push_back(holds[i]);
    }
    return temp;
}

bool item::candelete() {
    if (loans.size() == 0 && holds.size() == 0)
        return true;
    return false;
}

string item::issue(user* u){
    string message = st->issue(u,this,st);
    file->save();
    return message;
}

string item::placeOnHold(user* u){
    string message = st->placeOnHold(u,this,st);
    file->save();
    return message;
}

string item::checkIn(user * u){
    string message = st->checkIn(u,this,st);
    qDebug() << "IN ITEM , CALLING CHECK IN";
    file->save();
    return message;
}

string item::renew(user * u){
    string message = st->renew(u,this,st);
    file->save();
    return message;
}
