#ifndef BOOK_H
#define BOOK_H
#include "item.h"
#include <string>

using namespace std;

class book:public item
{
public:
    book();
    book(string,string,string,string,string);
};

#endif // BOOK_H
