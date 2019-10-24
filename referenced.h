#ifndef REFERENCED_H
#define REFERENCED_H
#include "state.h"
#include "user.h"
#include "item.h"
#include <string>

using namespace std;

class referenced:public state
{
public:
    referenced();
    string issue(user*,item*,state*&);
    string placeOnHold(user*,item*,state*&);
    string checkIn(user*,item*,state*&);
    string renew(user*,item*,state*&);
    ~referenced();
};

#endif // REFERENCED_H
