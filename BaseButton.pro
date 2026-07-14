#-------------------------------------------------
#
# Project created by QtCreator 2019-06-04T14:30:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaseButton
TEMPLATE = app


SOURCES += main.cpp\
        buttons/basepushbutton.cpp \
        buttons/basetoolbutton.cpp \
        widget.cpp

HEADERS  += widget.h \
    buttons/basepushbutton.h \
    buttons/basetoolbutton.h

FORMS    += widget.ui
