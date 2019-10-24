#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "user.h"
#include <string>

using namespace std;

class librarian:public user
{
public:
    librarian();
    librarian(string,string,string,string,string);
};

#endif // LIBRARIAN_H
