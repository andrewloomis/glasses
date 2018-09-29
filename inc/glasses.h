#ifndef GLASSES_H
#define GLASSES_H

#include <gesturecontroller.h>
#include <button.h>
#include <atomic>
#include <memory>

class Glasses
{
public:
    Glasses();
    void testGestures();
private:
    GestureController gc;
    Button wakeUp;
    
    static std::shared_ptr<std::atomic<bool>> shutdownFlag;
    static void signal_callback(int signal);
};

#endif