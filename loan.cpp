#include "loan.h"
#include "user.h"
#include "item.h"

loan::loan()
{

}

loan::loan(user *u, item *i, string idate,string status){
    this->u = u;
    this->i = i;
    this->idate = idate;
    setstatus(status);
    u->addloan(this);
    i->addloan(this);
}

user * loan::getUser() {
    return u;
}

item * loan::getItem() {
    return i;
}

string loan::getdate() {
    return idate;
}

void loan::setstatus(string status) {
    this->status = status;
}

string loan::getstatus() {
    return status;
}
