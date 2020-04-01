QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera_control.cpp \
    eel_detect.cpp \
    main.cpp \
    mainwindow.cpp \
    setting_dialog.cpp

HEADERS += \
    camera_control.h \
    eel_detect.h \
    mainwindow.h \
    setting_control.h \
    setting_dialog.h

FORMS += \
    mainwindow.ui \
    setting_dialog.ui

TRANSLATIONS += \
    eel_sorter_ko_KR.ts

INCLUDEPATH += C:\\OpenCV-4.1.1\\build\\include

LIBS += -LC:\OpenCV-4.1.1\build\x64\vc16\lib \
    -lopencv_world411 \
    -lopencv_world411d

QMAKE_CXXFLAGS += /utf-8

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
