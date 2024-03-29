QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += sanitizer sanitize_address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    src/geometry.cpp \
    src/interactivegraphicsscene.cpp \
    src/link.cpp \
    src/main.cpp \
    src/node.cpp \
    src/nodenotifier.cpp \
    src/triangulator.cpp \
    src/widget.cpp

HEADERS += \
    src/geometry.h \
    src/interactivegraphicsscene.h \
    src/link.h \
    src/node.h \
    src/nodenotifier.h \
    src/triangulator.h \
    src/widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
