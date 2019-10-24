#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class loan;
class hold;

class user
{
    friend class Filing;
protected:
    vector <loan*> loans;
    vector <hold*> holds;
    string id;
    string pw;
    string name;
    string address;
    string telephone;
public:
    user();
    user(string,string,string,string,string);
    void addloan(loan*);
    void addHold(hold*);
    string getid();
    string getname();
    string getaddress();
    string getphone();
    string getpw();
    void setid(string);
    void setname(string);
    void setaddress(string);
    void settelephone(string);
    vector <loan*> booksissued();
    vector <hold*>bookshold();
    bool matchpassword(string);
    virtual ~user(){}
};

#endif // USER_H
