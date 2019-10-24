#ifndef FILING_H
#define FILING_H
#include <string>

using namespace std;


class Filing
{
private:
    string mys;
public:
    Filing();
    void setusers();
    void setitems();
    void setloans();
    void setholds();
    void save();
};

#endif // FILING_H
