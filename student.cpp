#include "user.h"
#include "student.h"

student::student()
{
}

student::student(string id, string pw, string name, string address, string telephone)
    :user(id,pw,name,address,telephone){

}
