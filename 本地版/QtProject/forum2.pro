#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T18:37:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = forum2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        login.cpp \
    user.cpp \
    mainwindow.cpp \
    post.cpp \
    comment.cpp \
    viewpage.cpp \
    postpage.cpp \
    controller.cpp \
    board.cpp \
    useraddpage.cpp

HEADERS += \
        login.h \
    user.h \
    mainwindow.h \
    post.h \
    comment.h \
    viewpage.h \
    postpage.h \
    controller.h \
    board.h \
    useraddpage.h

FORMS += \
        login.ui \
    mainwindow.ui \
    viewpage.ui \
    postpage.ui \
    useraddpage.ui

RESOURCES += \
    style.qrc

RC_ICONS = logo.ico
