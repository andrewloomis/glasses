#ifndef GESTUREMANAGER_H
#define GESTUREMANAGER_H

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
    void setupCallbacks();
#else
    void setupCallbacks() {}
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
