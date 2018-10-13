#ifndef GLASSES_H
#define GLASSES_H

#include <gesturecontroller.h>
#include <button.h>
#include <swipemanager.h>
#include <bluetoothcontroller.h>
#include <timemanager.h>
#include <smsmanager.h>

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
    std::shared_ptr<SwipeManager> getSwipeManager() { return gc.getSwipeManager(); }
    std::shared_ptr<TimeManager> getTimeManager() { return tm; }
    std::shared_ptr<SmsManager> getSmsManager() { return sm; }
//    void testGestures();
private:
    GestureController gc;
    BluetoothController bc;
    std::shared_ptr<TimeManager> tm;
    std::shared_ptr<SmsManager> sm;
    QGuiApplication& guiApp;
    Button wakeUp;
    std::thread timerThread;
    
    static inline std::shared_ptr<std::atomic<bool>> shutdownFlag;
    static void signal_callback(int signal);
    void timer();
};

#endif
