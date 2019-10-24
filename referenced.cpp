#include "referenced.h"
#include <iostream>
using namespace std;

referenced::referenced(){
}

string referenced::issue(user*, item*, state*&s){
    return("Book is a reference book");
}

string referenced::placeOnHold(user*, item*, state*&s) {
    return("Book is a reference book");
}

string referenced::checkIn(user*, item*, state*&s) {
    return("You can not check in a referenced book");
}

string referenced::renew(user*, item*, state*&s){
    return ("You can not renew a reference book");
}
