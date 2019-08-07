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

HEADERS = \
   $$PWD/ak/ak.h \
   $$PWD/ak/ak_dbg.h \
   $$PWD/ak/message.h \
   $$PWD/ak/port.h \
   $$PWD/ak/timer.h \
   $$PWD/app/task/task.h \
   $$PWD/app/app.h \
   $$PWD/app/app_config.h \
   $$PWD/app/app_data.h \
   $$PWD/app/app_dbg.h \
   $$PWD/app/task_console.h \
   $$PWD/app/task_list.h \
   $$PWD/app/task_sys.h \
   $$PWD/app/time_lapse.h \
   $$PWD/CameraControllerApi/include/Api.h \
   $$PWD/CameraControllerApi/include/api_app.h \
   $$PWD/CameraControllerApi/include/Base64.h \
   $$PWD/CameraControllerApi/include/CameraController.h \
   $$PWD/CameraControllerApi/include/Command.h \
   $$PWD/CameraControllerApi/include/debug.h \
   $$PWD/CameraControllerApi/include/Helper.h \
   $$PWD/CameraControllerApi/include/Server.h \
   $$PWD/CameraControllerApi/include/Settings.h \
   $$PWD/common/base64.h \
   $$PWD/common/cmd_line.h \
   $$PWD/common/fifo.h \
   $$PWD/common/firmware.h \
   $$PWD/common/jsmn.h \
   $$PWD/common/json.hpp \
   $$PWD/driver/gpio.h \
   $$PWD/driver/rs232.h \
   $$PWD/driver/spi.h \
   $$PWD/sys/sys_boot.h \
   $$PWD/sys/sys_dbg.h \
   $$PWD/mainwindow.h

SOURCES = \
   $$PWD/ak/ak.cpp \
   $$PWD/ak/fsm.cpp \
   $$PWD/ak/message.cpp \
   $$PWD/ak/timer.cpp \
   $$PWD/ak/tsm.cpp \
   $$PWD/app/task/task.cpp \
   $$PWD/app/app.cpp \
   $$PWD/app/app_config.cpp \
   $$PWD/app/app_data.cpp \
   $$PWD/app/task_list.cpp \
   $$PWD/app/time_lapse.cpp \
   $$PWD/CameraControllerApi/src/Api.cpp \
   $$PWD/CameraControllerApi/src/api_app.cpp \
   $$PWD/CameraControllerApi/src/Base64.cpp \
   $$PWD/CameraControllerApi/src/CameraController.cpp \
   $$PWD/CameraControllerApi/src/Command.cpp \
   $$PWD/CameraControllerApi/src/Helper.cpp \
   $$PWD/CameraControllerApi/src/Server.cpp \
   $$PWD/CameraControllerApi/src/Settings.cpp \
   $$PWD/common/base64.cpp \
   $$PWD/common/cmd_line.cpp \
   $$PWD/common/fifo.cpp \
   $$PWD/common/firmware.cpp \
   $$PWD/common/jsmn.cpp \
   $$PWD/driver/gpio.c \
   $$PWD/driver/rs232.c \
   $$PWD/driver/spi.c \
   $$PWD/driver/spi_test.c \
   $$PWD/sys/sys_dbg.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/ak \
    $$PWD/app \
    $$PWD/app/task \
    $$PWD/CameraControllerApi/include \
    $$PWD/common \
    $$PWD/driver \
    $$PWD/sys

#DEFINES = 

