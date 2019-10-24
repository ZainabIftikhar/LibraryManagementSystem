#ifndef AVAILABLE_H
#define AVAILABLE_H

#include "state.h"
#include "user.h"
#include "item.h"
#include <string>

using namespace std;

class available:public state
{
public:
    available();
    string issue(user*,item*);
    string issue(user*,item*,state*&);
    string placeOnHold(user*,item*,state*&);
    string checkIn(user*,item*,state*&);
    string renew(user*,item*,state*&);
    ~available();
};

#endif // AVAILABLE_H
