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
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Programmer.cpp \
    QuickKeys.cpp \
    Stage.cpp \
    colorpicker.cpp \
    controller.cpp \
    customgraphic.cpp \
    dials.cpp \
    fixture.cpp \
    fixturedetails.cpp \
    form.cpp \
    leftcontrols.cpp \
    main.cpp \
    mainwindow.cpp \
    mbuttons.cpp \
    popup.cpp \
    qtrectitem.cpp \
    rightcontrols.cpp \
    setup.cpp \
    shadowlib.cpp \
    songlist.cpp \
    userinput.cpp

HEADERS += \
    Programmer.h \
    QuickKeys.h \
    Stage.h \
    colorpicker.h \
    controller.h \
    customgraphic.h \
    dials.h \
    fixture.h \
    fixturedetails.h \
    form.h \
    globalData.h \
    globalData.h \
    leftcontrols.h \
    mainwindow.h \
    mbuttons.h \
    popup.h \
    qtrectitem.h \
    rightcontrols.h \
    setup.h \
    shadowlib.h \
    songlist.h \
    userinput.h

FORMS += \
    FixFunction.ui \
    Programmer.ui \
    QuickKeys.ui \
    Stage.ui \
    colorpicker.ui \
    controller.ui \
    dials.ui \
    fixture.ui \
    fixturedetails.ui \
    form.ui \
    leftcontrols.ui \
    mainwindow.ui \
    rightcontrols.ui \
    setup.ui \
    userinput.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    LightProject.qrc

DISTFILES +=
