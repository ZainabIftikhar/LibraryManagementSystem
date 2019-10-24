#include "hold.h"
#include "user.h"
#include "item.h"

hold::hold()
{

}

hold::hold(user *u, item *i, string hdate,string status){
    this->u = u;
    this->i = i;
    this->hdate = hdate;
    setstatus(status);
    u->addHold(this);
    i->addHold(this);
}

user * hold::getUser() {
    return u;
}

item * hold::getItem() {
    return i;
}

string hold::getdate() {
    return hdate;
}

void hold::setstatus(string status) {
    this->status = status;
}


string hold::getstatus() {
    return status;
}
