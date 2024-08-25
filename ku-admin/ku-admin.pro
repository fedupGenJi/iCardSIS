QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CopyDatabase.cpp \
    addtoku.cpp \
    auditInput.cpp \
    canteen.cpp \
    canteenMain.cpp \
    change_num.cpp \
    data_addpage.cpp \
    data_removepage.cpp \
    kuToAudit.cpp \
    kuToTransport.cpp \
    main.cpp \
    mainpage.cpp \
    phoneNId.cpp \
    reg_admin.cpp \
    registrationMain.cpp \
    remove_regpage.cpp \
    sqlite/shell.c \
    sqlite/sqlite3.c \
    updatedb.cpp

HEADERS += \
    CopyDatabase.hpp \
    DatabaseHelper.h \
    DatabaseModel.h \
    addtoku.h \
    auditInput.h \
    canteen.h \
    canteenMain.h \
    change_num.h \
    data_addpage.h \
    data_removepage.h \
    kuToAudit.hpp \
    kuToTransport.h \
    mainpage.h \
    phoneNId.h \
    reg_admin.h \
    registrationMain.hpp \
    remove_regpage.h \
    sqlite/sqlite3.h \
    sqlite/sqlite3ext.h \
    updatedb.h

FORMS += \
    addtoku.ui \
    canteen.ui \
    change_num.ui \
    data_addpage.ui \
    data_removepage.ui \
    mainpage.ui \
    reg_admin.ui \
    remove_regpage.ui \
    updatedb.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
