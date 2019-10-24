#include "filing.h"
#include "lms.h"
#include "user.h"
#include "student.h"
#include "librarian.h"
#include "clerk.h"
#include "item.h"
#include "book.h"
#include "dvd.h"
#include "loan.h"
#include "hold.h"
#include "state.h"
#include "available.h"
#include "onhold.h"
#include "referenced.h"

#include <vector>
#include <string.h>
#include <QFile>
#include <QString>
#include <QtCore>
#include <QTextStream>
#include <QDebug>
#include <typeinfo>

extern lms *obj;

Filing::Filing()
{
    QFile inFile("C:/Users/Ali/Documents/Qt/LMS/myfile.txt");
    if (inFile.open(QIODevice::ReadOnly)) {
        QTextStream textStream(&inFile);
        QString line = textStream.readAll();
        inFile.close();
        mys = line.toLocal8Bit().constData();
        setusers();
        setitems();
        setloans();
        setholds();
    }
}

void Filing::setusers() {
    vector <string> elems;
    while ((mys.find('#'))!=0) {
        for (int i = 0; i < 6; i++) {
            if ((i%6)!=5) {
                elems.push_back((mys.substr(0, mys.find(44))));
                int len = elems[i].size()+1;
                mys.erase(0,len);
            }
            else {
                elems.push_back((mys.substr(0, mys.find(13))));
                int len = elems[i].size()+2;
                mys.erase(0,len);
                user * ptr;
                if (elems[0] == "S")
                    ptr = new student(elems[1],elems[2],elems[3],elems[4], elems[5]);
                else if (elems[0] == "C")
                    ptr = new clerk(elems[1],elems[2],elems[3],elems[4], elems[5]);
                else if (elems[0] == "L")
                    ptr = new librarian(elems[1],elems[2],elems[3],elems[4], elems[5]);

                obj->adduser(ptr);
                elems.clear();
                elems.shrink_to_fit();
            }
        }
    }
    mys.erase(0,3);
}

void Filing::setitems() {
    vector <string> elems;
    while ((mys.find('#'))!=0) {
        for (int i = 0; i < 6; i++) {
            if ((i%6)!=5) {
                elems.push_back((mys.substr(0, mys.find(44))));
                int len = elems[i].size()+1;
                mys.erase(0,len);
            }
            else {
                elems.push_back((mys.substr(0, mys.find(13))));
                int len = elems[i].size()+2;
                mys.erase(0,len);
                item * ptr;
                if (elems[0] == "B")
                    ptr = new book(elems[1],elems[2],elems[3],elems[4],elems[5]);
                else if (elems[0] == "D")
                    ptr = new dvd(elems[1],elems[2],elems[3],elems[4], elems[5]);

                obj->additem(ptr);
                elems.clear();
                elems.shrink_to_fit();
            }
        }
    }
    mys.erase(0,3);
}

void Filing::setloans() {
    vector <string> elems;
    while ((mys.find('#'))!=0) {
        for (int i = 0; i < 4; i++) {
            if ((i%4)!=3) {
                elems.push_back((mys.substr(0, mys.find(44))));
                int len = elems[i].size()+1;
                mys.erase(0,len);
            }
            else {
                elems.push_back((mys.substr(0, mys.find(13))));
                int len = elems[i].size()+2;
                mys.erase(0,len);
                user* username = obj->searchuser(elems[0]);
                item* itemname = obj->searchitem(elems[1]);
                loan * object = new loan(username, itemname, elems[2],elems[3]);
                elems.clear();
                elems.shrink_to_fit();
            }
        }
    }
     mys.erase(0,3);
}


void Filing::setholds() {
    vector <string> elems;
    while ((mys.find('#'))!=0) {
        for (int i = 0; i < 4; i++) {
            if ((i%4)!=3) {
                elems.push_back((mys.substr(0, mys.find(44))));
                int len = elems[i].size()+1;
                mys.erase(0,len);
            }
            else {
                elems.push_back((mys.substr(0, mys.find(13))));
                int len = elems[i].size()+2;
                mys.erase(0,len);
                user* username = obj->searchuser(elems[0]);
                item* itemname = obj->searchitem(elems[1]);
                hold * object = new hold(username, itemname, elems[2],elems[3]);
                elems.clear();
                elems.shrink_to_fit();
            }
        }
    }
}

void Filing::save() {
    QFile outFile("C:/Users/Ali/Documents/Qt/LMS/pw.txt");
    if (outFile.open(QIODevice::WriteOnly)) {

        //Save Users
        for (int i = 0; i < obj->users.size() ; i++) {
            QString temp = typeid(*(obj->users[i])).name();
            if (temp == "class student")
                outFile.write("S");
            else if (temp == "class clerk")
                outFile.write("C");
            else if (temp == "class librarian")
                outFile.write("L");
            outFile.write(",");
            outFile.write((obj->users[i]->getid()).c_str());
            outFile.write(",");
            outFile.write((obj->users[i]->getpw()).c_str());
            outFile.write(",");
            outFile.write((obj->users[i]->getname()).c_str());
            outFile.write(",");
            outFile.write((obj->users[i]->getaddress()).c_str());
            outFile.write(",");
            outFile.write((obj->users[i]->getphone()).c_str());
            outFile.write("\r\n");
        }
        outFile.write("#\r\n");

        //Save Items

        for (int i = 0; i < obj->items.size() ; i++) {
            QString temp = typeid(*(obj->items[i])).name();
            if (temp == "class book")
                outFile.write("B");
            else if (temp == "class dvd")
                outFile.write("D");
            outFile.write(",");
            outFile.write((obj->items[i]->getid()).c_str());
            outFile.write(",");
            outFile.write((obj->items[i]->gettitle()).c_str());
            outFile.write(",");
            outFile.write((obj->items[i]->getauthor()).c_str());
            outFile.write(",");
            outFile.write((obj->items[i]->getsubject()).c_str());
            outFile.write(",");
            temp = typeid(*(obj->items[i]->st)).name();
            if (temp == "class available")
                outFile.write("available");
            else if (temp == "class issued")
                outFile.write("issued");
            else if (temp == "class onhold")
                outFile.write("onhold");
            else if (temp == "class referenced")
                outFile.write("referenced");
            outFile.write("\r\n");
        }
        outFile.write("#\r\n");

        for (int i = 0; i < obj->users.size() ; i++) {
            for (int j = 0; j < (obj->users[i]->loans.size()) ; j++) {
                outFile.write((obj->users[i]->getid()).c_str());
                outFile.write(",");
                outFile.write(((obj->users[i]->loans[j]->getItem())->getid()).c_str());
                outFile.write(",");
                outFile.write((obj->users[i]->loans[j]->getdate()).c_str());
                outFile.write(",");
                outFile.write((obj->users[i]->loans[j]->getstatus()).c_str());
                outFile.write("\r\n");
              }
        }
        outFile.write("#\r\n");

        for (int i = 0; i < obj->users.size() ; i++) {
            for (int j = 0; j < obj->users[i]->holds.size() ; j++) {
                outFile.write((obj->users[i]->getid()).c_str());
                outFile.write(",");
                outFile.write((obj->users[i]->holds[j]->getItem()->getid()).c_str());
                outFile.write(",");
                outFile.write((obj->users[i]->holds[j]->getdate()).c_str());
                outFile.write(",");
                outFile.write((obj->users[i]->holds[j]->getstatus()).c_str());
                outFile.write("\r\n");
              }
        }
        outFile.write("#\r\n");
        outFile.flush();
        outFile.close();
    }
}




