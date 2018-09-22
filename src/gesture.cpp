#include <gesture.h>
#include <iostream>
#include <array>

// Pins
#define I2C_BUS 0
#define INT 33

// Registers
#define EN 0x80
#define GCONF1 0xA2
#define GCONF2 0xA3
#define GCONF3 0xAA
#define GCONF4 0xAB
#define GPULSE 0xA6
#define GFLVL 0xAE
#define GSTATUS 0xAF
#define GFIFO_U 0xFC
#define GFIFO_D 0xFD
#define GFIFO_L 0xFE
#define GFIFO_R 0xFF

void test() {}

GestureController::GestureController()
    : i2c(I2C_BUS), interrupt(INT)
{
    i2c.frequency(mraa::I2cMode::I2C_FAST);
    if (i2c.address(0x39) != mraa::Result::SUCCESS)
    {
        std::cout << "Device address invalid\n";
    }

    interrupt.dir(mraa::DIR_IN);
    interrupt.isr(mraa::Edge::EDGE_FALLING, intCallback, this);
    powerMode(PowerMode::ON);
    enableGestures();
}

GestureController::~GestureController()
{
    powerMode(PowerMode::OFF);
}

void GestureController::powerMode(PowerMode mode)
{
    // Set GEN and PON to 1
    i2c.writeReg(EN, 0x40 + static_cast<int>(mode));
}

void GestureController::enableGestures()
{
    // Enable hardware interrupt and gesture mode
    i2c.writeReg(GCONF4, 0x03);
}

void GestureController::intCallback(void* data)
{
    GestureController* gc = reinterpret_cast<GestureController*>(data);
    std::cout << "Interrupt\n";
    gc->readGestureData();
    gc->enableGestures();
}

void GestureController::readGestureData()
{
    uint8_t dataCounts = i2c.readReg(GFLVL);
    std::array<uint8_t, 128> fifoBuffer;
    if (dataCounts)
    {
        i2c.readBytesReg(GFIFO_U, fifoBuffer.data(), dataCounts * 4);
        parseFifoData(fifoBuffer, dataCounts);
    }
    else
    {
        std::cout << "No FIFO data\n";
    }
}

void GestureController::parseFifoData(std::array<uint8_t, 128>& data, uint8_t dataCount)
{
    for(int i = 0; i < dataCount * 4; i += 4)
    {
        gestureData.upData += data[i];
        gestureData.downData += data[i + 1];
        gestureData.leftData += data[i + 2];
        gestureData.rightData += data[i + 3];
    }

    gestureData.upData /= dataCount;
    gestureData.downData /= dataCount;
    gestureData.leftData /= dataCount;
    gestureData.rightData /= dataCount;
}

void GestureController::printData()
{
    std::cout << "Up: " << gestureData.upData
        << "\nDown: " << gestureData.downData
        << "\nRight: " << gestureData.rightData
        << "\nLeft: " << gestureData.leftData 
        << "\n------------" << std::endl;
}