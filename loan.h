#ifndef LOAN_H
#define LOAN_H

#include <string>
using namespace std;

class user;
class item;

class loan
{
private:
    string idate;
    string status;
    user *u;
    item *i;
public:
    loan();
    loan(user*,item*,string,string);
    user *getUser();
    item *getItem();
    string getdate();
    void setstatus(string);
    string getstatus();
};

#endif // LOAN_H
