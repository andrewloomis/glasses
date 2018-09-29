#ifndef BUTTON_H
#define BUTTON_H

#include <mraa.hpp>

class Button
{
public:
    Button(int gpioNumber);
    
private:
    mraa::Gpio gpio;
};

#endif