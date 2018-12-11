#ifndef GLASSES_H
#define GLASSES_H

#include <gesturemanager.h>
#include <bluetoothcontroller.h>
#include <timemanager.h>
#include <smsmanager.h>
#include <authenticationmanager.h>

#include <atomic>
#include <memory>
#include <QPointer>
#include <QGuiApplication>
#include <thread>

class Glasses
{
public:
    Glasses(QGuiApplication& app);
    ~Glasses();
    std::shared_ptr<GestureManager> getGestureManager() { return gestureManager; }
    std::shared_ptr<TimeManager> getTimeManager() { return timeManager; }
    std::shared_ptr<SmsManager> getSmsManager() { return smsManager; }
    std::shared_ptr<AuthenticationManager> getAuthenticationManager()
        { return authenticationManager; }
//    void testGestures();

private:
    std::shared_ptr<GestureManager> gestureManager;
    BluetoothController bluetoothController;
    std::shared_ptr<TimeManager> timeManager;
    std::shared_ptr<SmsManager> smsManager;
    std::shared_ptr<AuthenticationManager> authenticationManager;

    QGuiApplication& guiApp;
    std::thread timerThread;
    
    static inline std::shared_ptr<std::atomic<bool>> shutdownFlag;
    static void signal_callback(int signal);
    void timer();
};

#endif
