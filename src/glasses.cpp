#include <glasses.h>

#include <mraa/common.hpp>
#include <iostream>     // cout
#include <chrono>       // chrono_literals
#include <thread>       // sleep_for
#include <signal.h>     // signal()

void Glasses::signal_callback(int signal)
{
    *shutdownFlag = true;
}

Glasses::Glasses()
    : wakeUp(31)
{
    signal(SIGINT, signal_callback);
    shutdownFlag = std::make_shared<std::atomic<bool>>(false);

    // Configure MRAA library
    mraa::Result res = mraa::init();
    if (res != mraa::Result::SUCCESS)
    {
        std::cout << "MRAA failed\n";
        exit(1);
    }
    else
    {
        std::cout << "Using MRAA " << mraa::getVersion() 
        << " on " << mraa::getPlatformName() << std::endl;
    }
}

void Glasses::testGestures()
{
    while(!(*shutdownFlag))
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
    }
    std::cout << "Latest Gesture: " << (int)gc.getLatestGesture().dir
    << " at " << gc.getLatestGesture().timestamp << std::endl;
}
