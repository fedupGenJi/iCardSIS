QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LibManager.cpp \
    addpage.cpp \
    auditInput.cpp \
    fine.cpp \
    fourthpage.cpp \
    functiondialog.cpp \
    main.cpp \
    kulibrary.cpp \
    secondpage.cpp \
    sqlite/shell.c \
    sqlite/sqlite3.c

HEADERS += \
    LibManager.hpp \
    addpage.h \
    auditInput.h \
    fourthpage.h \
    functiondialog.h \
    kulibrary.h \
    secondpage.h \
    sqlite/sqlite3.h \
    sqlite/sqlite3ext.h

FORMS += \
    addpage.ui \
    fourthpage.ui \
    functiondialog.ui \
    kulibrary.ui \
    secondpage.ui

TRANSLATIONS +=
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
