#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T03:20:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMS
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    user.cpp \
    librarian.cpp \
    student.cpp \
    clerk.cpp \
    item.cpp \
    book.cpp \
    lms.cpp \
    loan.cpp \
    dvd.cpp \
    filing.cpp \
    studentform.cpp \
    clerkform.cpp \
    librarianform.cpp \
    hold.cpp \
    hold.cpp \
    state.cpp \
    available.cpp \
    issued.cpp \
    referenced.cpp \
    onhold.cpp

HEADERS  += interface.h \
    user.h \
    librarian.h \
    student.h \
    clerk.h \
    item.h \
    book.h \
    lms.h \
    loan.h \
    dvd.h \
    filing.h \
    studentform.h \
    clerkform.h \
    librarianform.h \
    hold.h \
    state.h \
    available.h \
    issued.h \
    referenced.h \
    onhold.h

FORMS    += interface.ui \
    studentform.ui \
    clerkform.ui \
    librarianform.ui

RESOURCES +=
