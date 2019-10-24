#include "book.h"
#include "item.h"
#include "string.h"
#include <iostream>
using namespace std;


book::book()
{
}

book::book(string id,string title, string author, string subject,string status)
    :item(id,title,author,subject,status)
{
}
