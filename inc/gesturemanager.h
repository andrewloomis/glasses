#ifndef GESTUREMANAGER_H
#define GESTUREMANAGER_H

#include <usertypes.h>
#ifdef PLATFORM_ARM
    #include <glassesDevices/gesturesensor.h>
    #include <glassesDevices/touchslider.h>
#endif
#include <memory>
#include <QObject>

class GestureManager : public QObject
{
    Q_OBJECT
public:
    GestureManager();
    ~GestureManager();

private:
#ifdef PLATFORM_ARM
    GestureSensor gestureSensor;
    TouchSlider touchSlider;
#endif

signals:
    void toRight();
    void toLeft();
    void toUp();
    void toDown();
    void toMessage();
    void select();
};

#endif
