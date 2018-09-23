#include <gesture.h>
#include <mraa/common.hpp>
#include <iostream>     // cout
#include <chrono>       // chrono_literals
#include <thread>       // sleep_for
#include <atomic>       // std::atomic
#include <signal.h>     // signal()

bool run = true;

void signal_callback(int signal)
{
    run = false;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signal_callback);

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

    GestureController gc;
    while(run)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
        
    }
    std::cout << "Latest Gesture: " << (int)gc.getLatestGesture().dir
    << " at " << gc.getLatestGesture().timestamp << std::endl;
}