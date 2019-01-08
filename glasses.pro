QT += quick bluetooth
CONFIG += c++17
PROJ_DIR = $${PWD}
SYSROOT = ${HOME}/dev/dragonboard/sysroot

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp    \
    src/glasses.cpp  \
    src/bluetoothcontroller.cpp \
    src/timemanager.cpp \
    src/smsmanager.cpp \
    src/authenticationmanager.cpp \
    src/gesturemanager.cpp \
    src/ledmanager.cpp

HEADERS += \
    inc/glasses.h \
    inc/bluetoothcontroller.h \
    inc/timemanager.h \
    inc/smsmanager.h \
    inc/authenticationmanager.h \
    inc/gesturemanager.h \
    inc/config.h \
    inc/ledmanager.h

RESOURCES += qml/qml.qrc

INCLUDEPATH += inc/

CONFIG(PLATFORM_DESKTOP) {
    DEFINES += PLATFORM_DESKTOP
}

CONFIG(PLATFORM_ARM) {
    DEFINES += PLATFORM_ARM

    INCLUDEPATH += $${PROJ_DIR}/glassesDevices/spdlog/include $${PROJ_DIR}/glassesDevices/

    target.path = /home/linaro/glasses-build
    INSTALLS += target

    LIBS += -L$${SYSROOT}/usr/lib/aarch64-linux-gnu -lglassesDevices

    DEPENDPATH += $${SYSROOT}/usr/lib/aarch64-linux-gnu
}

