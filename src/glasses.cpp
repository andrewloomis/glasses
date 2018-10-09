#include <glasses.h>

#include <mraa/common.hpp>
#include <iostream>     // cout
#include <chrono>       // chrono_literals
#include <signal.h>     // signal()
#include <QObject>

void Glasses::signal_callback(int signal)
{
    *shutdownFlag = true;
}

Glasses::Glasses(QGuiApplication& app)
    : tm(std::make_shared<TimeManager>()), guiApp(app), wakeUp(31)
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
    timerThread = std::thread([this]{ timer(); });

    QObject::connect(&bc, &BluetoothController::newTime, tm.get(), &TimeManager::updateTime);
}

Glasses::~Glasses()
{
    timerThread.join();
}

void Glasses::timer()
{
//    auto start = std::chrono::system_clock::now();
    uint8_t level = 100;
    while(!(*shutdownFlag))
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
//        auto now = std::chrono::system_clock::now();
//        std::chrono::duration<double> diff = now - start;
//        if (diff.count() > 12.0)
//        {
//            *shutdownFlag = true;
//        }
    }
    guiApp.quit();
}
