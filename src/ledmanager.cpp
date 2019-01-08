#ifdef PLATFORM_ARM
#include "ledmanager.h"

LEDManager::LEDManager()
{
    init();
}

void LEDManager::init()
{
    thread = std::thread([&]() {
        pulse(Color::Blue, 2);
    });
}

void LEDManager::pulse(Color color, int repetitions)
{
    switch (color)
    {
    case Color::Blue:
        for (int i = 0; i < repetitions; i++)
        {
            for (int b = 0; b < 255; b++)
            {
                led.setColor(0, 0, b);
            }
            for (int b = 255; b > 0; b--)
            {
                led.setColor(0, 0, b);
            }
        }
        break;
    }
}
#endif
