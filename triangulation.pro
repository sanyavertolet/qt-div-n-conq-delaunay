QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Changed to 20!
CONFIG += c++17
CONFIG += sanitizer sanitize_address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    geometry.cpp \
    interactivegraphicsscene.cpp \
    link.cpp \
    main.cpp \
    node.cpp \
    nodenotifier.cpp \
    triangulator.cpp \
    widget.cpp

HEADERS += \
    geometry.h \
    interactivegraphicsscene.h \
    link.h \
    node.h \
    nodenotifier.h \
    triangulator.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
