#include "interface.h"
#include <iostream>
#include "lms.h"
#include "filing.h"
#include "state.h"
#include "available.h"
#include "issued.h"
#include "onhold.h"
#include "referenced.h"
#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;

lms *obj;
Filing *file;
interface *w;
state * aObj;
state * iObj;
state * hObj;
state * rObj;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    obj = new lms();
    aObj = new available();
    iObj = new issued();
    hObj = new onhold();
    rObj = new referenced();

    file = new Filing();
    w = new interface;
    w->show();
    return a.exec();
}
