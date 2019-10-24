#include "user.h"
#include "loan.h"
#include "hold.h"

user::user(){

}

user::user(string id, string pw, string name, string address, string telephone){
    this->id = id;
    this->pw = pw;
    setname(name);
    setaddress(address);
    settelephone(telephone);
}

void user::addloan(loan *l) {
    loans.push_back(l);
}

void user::addHold(hold *l) {
    holds.push_back(l);
}

void user::setaddress(string address) {
    this->address = address;
}

void user::setname(string name) {
    this->name = name;
}

void user::settelephone(string telephone) {
    this->telephone = telephone;
}

void user::setid(string id) {
    this->id = id;
}

string user::getid(){
    return id;
}

string user::getpw(){
    return pw;
}

string user::getname(){
    return name;
}

string user::getaddress(){
    return address;
}

string user::getphone(){
    return telephone;
}

vector <loan *> user::booksissued() {
    vector <loan*> temp;
    for (int i = 0; i < loans.size(); i++) {
        if (loans[i]->getstatus() == "not returned")
            temp.push_back(loans[i]);
    }
    return temp;
}

vector <hold*>user::bookshold() {
    vector <hold*> temp;
    for (int i = 0; i < holds.size(); i++) {
        if (holds[i]->getstatus() == "not issued")
            temp.push_back(holds[i]);
    }
    return temp;
}

bool user::matchpassword(string pw) {
    if (this->pw == pw)
        return true;
    return false;
}

