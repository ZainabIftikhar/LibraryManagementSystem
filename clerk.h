#ifndef CLERK_H
#define CLERK_H

#include "user.h"
#include "string.h"

using namespace std;
class clerk:public user
{
public:
    clerk();
    clerk(string,string,string,string,string);
};

#endif // CLERK_H
