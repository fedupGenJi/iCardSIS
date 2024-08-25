QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity.cpp \
    addbalance.cpp \
    auditInput.cpp \
    balance.cpp \
    balanceOperation.cpp \
    books.cpp \
    busSubscription.cpp \
    databaseOperation.cpp \
    fineOperation.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    payfine.cpp \
    registration.cpp \
    regpage.cpp \
    studentInfo.cpp \
    subscription.cpp \
    transferbalance.cpp \
    transportation.cpp \
    vendors/sqlite/shell.c \
    vendors/sqlite/sqlite3.c

HEADERS += \
    activity.h \
    addbalance.h \
    auditInput.h \
    balance.h \
    books.h \
    homepage.h \
    include/balanceOperation.h \
    include/busSubscription.h \
    include/databaseOperation.h \
    include/fineOperation.h \
    mainwindow.h \
    payfine.h \
    registration.h \
    regpage.h \
    studentInfo.h \
    subscription.h \
    transferbalance.h \
    transportation.h \
    vendors/sqlite/sqlite3.h \
    vendors/sqlite/sqlite3ext.h

FORMS += \
    activity.ui \
    addbalance.ui \
    balance.ui \
    books.ui \
    homepage.ui \
    mainwindow.ui \
    payfine.ui \
    regpage.ui \
    subscription.ui \
    transferbalance.ui \
    transportation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/src.qrc \
    src.qrc \
    src.qrc \
    src.qrc \
    src.qrc

DISTFILES +=
