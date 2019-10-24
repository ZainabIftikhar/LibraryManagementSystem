#ifndef LMS_H
#define LMS_H
#include <vector>
#include <string>
#include "filing.h"
#include "hold.h"
#include <QDate>
class Filing;

using namespace std;
class user;
class item;
class loan;

class lms
{
    friend class Filing;
private:
    vector <user *>users;
    vector <item *>items;
public:
    lms();
    vector <item*> searchtitle(string);
    vector <item*> searchauthor(string);
    vector <item*> searchsubject(string);

    user* searchuser(string id);
    item* searchitem(string id);
    loan* searchloan(item*,user*);
    hold* searchhold(item*,user*);
    void additem(item*);
    void adduser(user*);


    string placehold(item*, user*);
    string checkIn(item*, user*);
    string checkOut(item*, user*);
    string renew(item*, user*);
    string calculatefine(string, QDate);

    string addnewuser(string,string,string,string,string);
    string edituser(string,string,string,string,string);
    string addnewitem(string,string,string,string,string,string);
    string edititem(string,string,string,string,string);
    string deleteitem(string);
};

#endif // LMS_H
