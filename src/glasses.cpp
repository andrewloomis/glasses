#include <glasses.h>

#include <iostream>     // cout
#include <chrono>       // chrono_literals
#include <signal.h>     // signal()
#include <QObject>

void Glasses::signal_callback(int signal)
{
    *shutdownFlag = true;
}

Glasses::Glasses(QGuiApplication& app)
    : gestureManager(std::make_shared<GestureManager>()), timeManager(std::make_shared<TimeManager>()),
      smsManager(std::make_shared<SmsManager>()), authenticationManager(std::make_shared<AuthenticationManager>()),
      guiApp(app)
{
    signal(SIGINT, signal_callback);
    shutdownFlag = std::make_shared<std::atomic<bool>>(false);

    timerThread = std::thread([this]{ timer(); });

    QObject::connect(&bluetoothController, &BluetoothController::newTime, timeManager.get(), &TimeManager::updateTime);
    QObject::connect(&bluetoothController, &BluetoothController::newMessage, smsManager.get(), &SmsManager::updateMessage);
//    QObject::connect(smsManager.get(), &SmsManager::launchMessagePopup, gestureManager.get(), &SwipeManager::moveToMessage);
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
