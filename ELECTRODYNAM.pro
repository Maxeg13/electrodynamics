#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T10:36:06
#
#-------------------------------------------------
CONFIG   += qwt
QT       += core gui
QWT_F = QWT
INCLUDEPATH += C:/Qwt-6.1.3/include
LIBS += -LC:/Qwt-6.1.3/lib -lqwt


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ELECTRODYNAM
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
#        main.cpp \
#        mainwindow.cpp \
    drawing.cpp \
    main.cpp \
    mainwindow.cpp \
    free_space.c \
    fdtd_1d_maxwell.cpp \
    pulse.cpp

HEADERS += \
#        mainwindow.h \
    drawing.h \
    mainwindow.h \
    constants.h \
    fdtd_1d_maxwell.h \
    pulse.h

FORMS +=

DISTFILES += \
    fdtd_1d_maxwell.с \
#    fdtd_1d_maxwell.с \
#    fdtd_d_maxwell.с
