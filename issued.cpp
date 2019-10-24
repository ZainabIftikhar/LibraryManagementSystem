#include "issued.h"
#include "onhold.h"
#include "hold.h"
#include "loan.h"
#include "available.h"
#include "lms.h"
#include <iostream>
#include <QDate>
#include <QDebug>

using namespace std;

extern lms*obj;
extern state * aObj;
extern state * iObj;
extern state * hObj;
extern state * rObj;


issued::issued(){
}

string issued::issue(user*u ,item* i, state*&s){
    return( "Book is already issued to another user" );
}

string issued::placeOnHold(user*u, item*i, state*&s){
    hold *newhold = new hold(u,i,
                    (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                    "not issued");
    s = hObj;
    return( "Book placed on hold" );
}

string issued::checkIn(user*u, item*i, state*&s){
    qDebug () << "FINE 1";
    loan * temp = obj->searchloan(i,u);
    if (temp == NULL)
        return ("No loan exists for the given fields");
    temp->setstatus("returned");
    s = aObj;
    return("Book is checked in");
}

string issued::renew(user *u, item *i, state*&s){
    loan * temp = obj->searchloan(i,u);
    if (temp == NULL)
        return ("No loan exists for the given fields");
    temp->setstatus("returned");
    loan *newloan = new loan(u,i,
                    (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                     "not returned");
    return( "Book is renewed" );
}

issued::~issued(){
}
