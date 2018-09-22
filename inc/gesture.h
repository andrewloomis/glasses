#ifndef GESTURE_H
#define GESTURE_H

#include <mraa.hpp>
#include <functional>
class GestureController
{
public:
    GestureController();
    ~GestureController();
    void printData();

private:
    mraa::I2c i2c;
    mraa::Gpio interrupt;

    struct GestureData
    {
        int upData = 0;
        int downData = 0;
        int rightData = 0;
        int leftData = 0;
    } gestureData;

    enum class PowerMode
    {
        OFF = 0,
        ON = 1
    };

    void enableGestures();
    // std::function<void(void*)> intCallback;
    static void intCallback(void*);
    void readGestureData();
    void parseFifoData(std::array<uint8_t, 128>& data, uint8_t dataCount);
    void powerMode(PowerMode mode);
};

#endif