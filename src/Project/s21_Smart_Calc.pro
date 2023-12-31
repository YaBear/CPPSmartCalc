QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/Controller.cc \
    ../View/mainwindow.cc \
    main.cc \
    qcustomplot.cc

HEADERS += \
    ../Controller/Controller.h \
    ../Model/PolishNotationModel.h \
    ../Model/Calculate.h \
    ../Model/Converter.h \
    ../Model/Validator.h \
    ../View/mainwindow.h \
    qcustomplot.h

FORMS += \
    ../View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
