#ifndef GLASSES_H
#define GLASSES_H

#include <gesturecontroller.h>
#include <button.h>
#include <swipemanager.h>
#include <bluetoothcontroller.h>

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
    QPointer<SwipeManager> getSwipeManager() { return gc.getSwipeManager(); }
//    void testGestures();
private:
    GestureController gc;
    BluetoothController bc;
    QGuiApplication& guiApp;
    Button wakeUp;
    std::thread timerThread;
    
    static inline std::shared_ptr<std::atomic<bool>> shutdownFlag;
    static void signal_callback(int signal);
    void timer();
};

#endif
