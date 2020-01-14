#-------------------------------------------------
#
# Project created by QtCreator 2019-12-20T09:41:39
#
#-------------------------------------------------

QT       += core gui
QT+=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RailMeasurement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    camerawindow.cpp \
    mat2qtformatmethod.cpp \
    cgxbitmap.cpp \
    convertstring.cpp \
    drawwidget.cpp \
    matio.cpp \
    cameracalib.cpp \
    laserplane.cpp \
    pointstocamera.cpp \
    pointstoworld.cpp \
    imgprofun.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    camerawindow.h \
    mat2qtformatmethod.h \
    cgxbitmap.h \
    convertstring.h \
    drawwidget.h \
    matio.h \
    cameracalib.h \
    laserplane.h \
    pointstocamera.h \
    pointstoworld.h \
    imgprofun.h

FORMS += \
        mainwindow.ui \
    camerawindow.ui

# opencv环境，添加了imgproc,core，highui库
# opencv环境，添加了calib3d库-2020.1.8
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_imgproc2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_imgproc2413d
else:unix: LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_imgproc2413

INCLUDEPATH += $$PWD/../../cvpack/package/opencv/build/include
DEPENDPATH += $$PWD/../../cvpack/package/opencv/build/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_core2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_core2413d
else:unix: LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_core2413

INCLUDEPATH += $$PWD/../../cvpack/package/opencv/build/include
DEPENDPATH += $$PWD/../../cvpack/package/opencv/build/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_highgui2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_highgui2413d
else:unix: LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_highgui2413

INCLUDEPATH += $$PWD/../../cvpack/package/opencv/build/include
DEPENDPATH += $$PWD/../../cvpack/package/opencv/build/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_calib3d2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_calib3d2413d
else:unix: LIBS += -L$$PWD/../../cvpack/package/opencv/build/x64/vc14/lib/ -lopencv_calib3d2413

INCLUDEPATH += $$PWD/../../cvpack/package/opencv/build/include
DEPENDPATH += $$PWD/../../cvpack/package/opencv/build/include

# 大恒sdk环境，添加了C++库和包含路径，没有添加c程序的库
unix|win32: LIBS += -L$$PWD/'../../CameraDemo/C++ SDK/lib/x64/' -lGxIAPICPPEx

INCLUDEPATH += $$PWD/'../../CameraDemo/C++ SDK/lib/x64'
DEPENDPATH += $$PWD/'../../CameraDemo/C++ SDK/lib/x64'

INCLUDEPATH += $$PWD/'../../CameraDemo/C++ SDK/inc'
DEPENDPATH += $$PWD/'../../CameraDemo/C++ SDK/inc'

CONFIG +=C++11

