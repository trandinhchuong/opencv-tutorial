#-------------------------------------------------
#
# Project created by QtCreator 2019-08-07T08:57:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ak_opencv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# add extra compiler
QMAKE_CXXFLAGS += -std=c++0x            \
                -Werror                 \
                -Wno-error               \
                -W                      \
                -Wno-missing-field-initializers         \
                -Wall			\
                -Winline		\
                -pipe			\
                -g

# /*add external library*/
LIBS += -L/usr/local/lib/ \
        -L/usr/include      \
        -lboost_system  -lgphoto2 -lmicrohttpd -lpthread -lexiv2  #using gphoto
INCLUDEPATH += sys/ \
               app/ \
               ak/  \
               app/task/ \
               CameraControllerApi/include/ \
               driver/ \
               common/
LIBS+=-lz -lrt -lm    # FIX ERROR timer_settime@@GLIBC_2.
CONFIG += c++11
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



FORMS += \
        mainwindow.ui

HEADERS += \
    ak/ak.h \
    ak/ak_dbg.h \
    ak/message.h \
    ak/port.h \
    ak/timer.h \
    app/task/task.h \
    app/app.h \
    app/app_config.h \
    app/app_data.h \
    app/app_dbg.h \
    app/task_console.h \
    app/task_list.h \
    app/task_sys.h \
    app/time_lapse.h \
    CameraControllerApi/include/Api.h \
    CameraControllerApi/include/api_app.h \
    CameraControllerApi/include/Base64.h \
    CameraControllerApi/include/CameraController.h \
    CameraControllerApi/include/Command.h \
    CameraControllerApi/include/debug.h \
    CameraControllerApi/include/Helper.h \
    CameraControllerApi/include/Server.h \
    CameraControllerApi/include/Settings.h \
    common/base64.h \
    common/cmd_line.h \
    common/fifo.h \
    common/firmware.h \
    common/jsmn.h \
    common/json.hpp \
    driver/gpio.h \
    driver/rs232.h \
    driver/spi.h \
    sys/sys_boot.h \
    sys/sys_dbg.h \
    mainwindow.h

SOURCES += \
    ak/ak.cpp \
    ak/fsm.cpp \
    ak/message.cpp \
    ak/timer.cpp \
    ak/tsm.cpp \
    app/task/task.cpp \
    app/app.cpp \
    app/app_config.cpp \
    app/app_data.cpp \
    app/task_list.cpp \
    app/time_lapse.cpp \
    CameraControllerApi/src/Api.cpp \
    CameraControllerApi/src/api_app.cpp \
    CameraControllerApi/src/Base64.cpp \
    CameraControllerApi/src/CameraController.cpp \
    CameraControllerApi/src/Command.cpp \
    CameraControllerApi/src/Helper.cpp \
    CameraControllerApi/src/Server.cpp \
    CameraControllerApi/src/Settings.cpp \
    common/base64.cpp \
    common/cmd_line.cpp \
    common/fifo.cpp \
    common/firmware.cpp \
    common/jsmn.cpp \
    sys/sys_dbg.cpp \
    main.cpp \
    mainwindow.cpp \
    driver/gpio.c \
    driver/rs232.c \
    driver/spi.c \
    driver/spi_test.c

