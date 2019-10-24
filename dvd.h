#ifndef DVD_H
#define DVD_H

#include "item.h"

class dvd:public item
{
public:
    dvd();
    dvd(string,string,string,string,string);
};

#endif // DVD_H
