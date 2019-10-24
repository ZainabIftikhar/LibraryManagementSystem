#ifndef hold_H
#define hold_H

#include "user.h"
#include "item.h"

class hold
{
private:
    string hdate;
    string status;
    user *u;
    item *i;
public:
    hold();
    hold(user*,item*,string,string);
    user *getUser();
    item *getItem();
    string getdate();
    string getstatus();
    void setstatus(string);
};

#endif // hold_H
