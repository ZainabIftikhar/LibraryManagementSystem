#ifndef ITEM_H
#define ITEM_H

#include "user.h"
#include "state.h"
#include <string>
#include <vector>
using namespace std;

class loan;
class hold;
class state;

class item
{
    friend class Filing;
public:
    item();
    virtual ~item() {
    }

    item(string,string,string,string,string);
    string getid();
    string gettitle();
    string getauthor();
    string getsubject();

    void setid(string);
    void settitle(string);
    void setauthor(string);
    void setsubject(string);
    void addloan(loan *);
    void addHold(hold *);

    vector <loan *> haveissued();
    vector <hold*>haveholded();
    bool candelete();

    string issue(user*);
    string placeOnHold(user*);
    string renew(user*);
    string checkIn(user*);

protected:
    string id;
    string title;
    string author;
    string subject;
    string status;
    vector <loan*>loans;
    vector <hold*> holds;
    state* st;
};

#endif // ITEM_H
