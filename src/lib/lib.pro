
TEMPLATE = lib
TARGET = plotline
QT += core gui
DEFINES += LIBPLOTLINE

HEADERS += chapter.h \
    character.h \
    completable.h \
    novel.h \
    plotline.h \
    scene.h \
    serializable.h

SOURCES += chapter.cpp \
    character.cpp \
    completable.cpp \
    novel.cpp \
    plotline.cpp \
    scene.cpp \
    serializable.cpp

CONFIG += c++11