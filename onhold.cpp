#include "onhold.h"
#include "issued.h"
#include "lms.h"
#include "loan.h"
#include "hold.h"
#include <iostream>
#include <QDate>
using namespace std;

extern lms* obj;
extern state * aObj;
extern state * iObj;
extern state * hObj;
extern state * rObj;

onhold::onhold(){
}

string onhold::issue(user*u, item*i, state*&s){
    hold * temp = obj ->searchhold(i,u);
    if (temp == NULL)
        return ("Book is on hold for another user. Can not issue");

    temp->setstatus("issued");
    loan *newloan = new loan(u,i,
                   (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                    "not returned");
    s = iObj;
    return ("Book is issued to the holder");
}

string onhold::placeOnHold(user*u, item*i, state*&s) {
    hold * temp = obj->searchhold(i,u);
    if (temp != NULL) {
        return ("A hold for the given user already exists");
    }
    hold *newhold = new hold(u,i,
                    (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                     "not issued");
    return( "Book placed on hold" );
}


string onhold::checkIn(user*u, item*i, state*&s) {
    loan * temp = obj->searchloan(i,u);
    if (temp == NULL)
        return ("No loan exists for the given fields");
    temp->setstatus("returned");
    return("Book is checked in");
}

string onhold::renew(user *u, item *i, state*&s) {
    loan * temp = obj->searchloan(i,u);
    if (temp == NULL)
        return ("No loan exists for the given fields");
    temp->setstatus("returned");
    return ("Book is on hold");
}

onhold::~onhold(){
}
