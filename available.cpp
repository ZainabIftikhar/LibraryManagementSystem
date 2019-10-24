#include "available.h"
#include "issued.h"
#include "onhold.h"
#include "book.h"
#include "loan.h"
#include "hold.h"
#include "filing.h"
#include <QDate>
#include <iostream>

extern state * aObj;
extern state * iObj;
extern state * hObj;
extern state * rObj;

using namespace std;

available::available(){
}

string available::issue(user* u ,item* i,state *&s){
    loan *newloan = new loan(u,i,
                    (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                     "not returned");
    s = iObj;
    return( "Book issued" );
}

string available::placeOnHold(user* u,item* i,state*&s) {
    hold *newhold = new hold(u,i,
                    (QDate::currentDate()).toString("dd-MM-yyyy").toLocal8Bit().constBegin(),
                    "not issued");
    s = hObj;
    return( "Book placed on hold" );
}

string available::checkIn(user*,item*,state*&s) {
    return( "You can not check in an available book" );
}

string available::renew(user *, item *,state*&s){
    return("You can not re-new an available book");
}

available::~available(){
}
