#ifndef ONHOLD_H
#define ONHOLD_H
#include "state.h"
#include "user.h"
#include "item.h"
#include <string>

using namespace std;

class onhold:public state
{
public:
    onhold();
    string issue(user*,item*,state*&);
    string placeOnHold(user*,item*,state*&);
    string checkIn(user*,item*,state*&);
    string renew(user*,item*,state*&);
    ~onhold();
};

#endif // ONHOLD_H
