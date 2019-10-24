#ifndef ISSUED_H
#define ISSUED_H
#include "state.h"
#include "user.h"
#include "item.h"
#include <string>

using namespace std;

class issued:public state
{
private:
    bool action;
public:
    issued();
    string issue(user*,item*,state*&);
    string placeOnHold(user*,item*,state*&);
    string checkIn(user*,item*,state*&);
    string renew(user*,item*,state*&);
    ~issued();
};

#endif // ISSUED_H
