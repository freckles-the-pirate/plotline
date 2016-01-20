######################################################################
# Automatically generated by qmake (3.0) Tue Jan 19 18:57:44 2016
######################################################################

TEMPLATE = app
TARGET = src
INCLUDEPATH += .

QT += core gui widgets

# Input
HEADERS += chapter.h \
           character.h \
           completable.h \
           mainwindow.h \
           novel.h \
           plotline.h \
           scene.h \
           sceneitemmodel.h \

FORMS += mainwindow.ui
SOURCES += chapter.cpp \
           character.cpp \
           completable.cpp \
           main.cpp \
           mainwindow.cpp \
           novel.cpp \
           plotline.cpp \
           scene.cpp \
           sceneitemmodel.cpp
RESOURCES += images.qrc

QMAKE_CXXFLAGS += -std=gnu++11
