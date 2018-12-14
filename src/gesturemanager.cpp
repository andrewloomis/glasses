#include <gesturemanager.h>

GestureManager::GestureManager()
{
    setupCallbacks();
}

GestureManager::~GestureManager()
{

}

#ifdef PLATFORM_ARM
void GestureManager::setupCallbacks()
{
    touchSlider.onRightFlick([&]{
        toRight();
    });
    touchSlider.onLeftFlick([&]{
        toLeft();
    });
    touchSlider.onTap([&]{
        select();
    });
}
#endif
