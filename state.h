#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <string>
#include "user.h"
using namespace std;

class item;

class state
{
public:
    state();
    virtual string issue(user*,item*,state*&) = 0;
    virtual string placeOnHold(user*,item*,state*&) = 0;
    virtual string checkIn(user*,item*,state*&) = 0;
    virtual string renew(user*,item*,state*&) = 0;
    ~state();
};

#endif // STATE_H
