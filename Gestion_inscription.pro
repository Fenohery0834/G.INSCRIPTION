QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET   = Gestion_inscription
TEMPLATE = app

SOURCES += \
    main.cpp \
    inscription.cpp \
    personne.cpp

HEADERS += \
    inscription.hpp \
    personne.hpp

FORMS += \
    inscription.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
