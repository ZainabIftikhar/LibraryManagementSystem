#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class student:public user
{
public:
    student();
    student(string,string,string,string,string);
};

#endif // STUDENT_H
