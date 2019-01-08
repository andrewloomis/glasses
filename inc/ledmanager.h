#ifdef PLATFORM_ARM
#ifndef LEDMANAGER_H
#define LEDMANAGER_H


#include <glassesDevices/rgbled.h>
#include <thread>

class LEDManager
{
public:
    LEDManager();

private:
    RGBLed led;
    std::thread thread;

    enum class Color
    {
        Red = 0,
        Green,
        Blue
    };
    void init();
    void pulse(Color color, int repetitions);
};

#endif // LEDMANAGER_H
#endif // PLATFORM_ARM
