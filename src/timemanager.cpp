#include "timemanager.h"
#include <iostream>

TimeManager::TimeManager(QObject *parent)
    : QObject(parent), mTime(QDate(0,0,2), QTime(0,0,0))
{

}

QString TimeManager::getDayOfWeek() const
{
    std::cout << "dow: " << (std::size_t)mTime.date().dayOfWeek() << '\n';
    return daysOfWeek[(std::size_t)mTime.date().dayOfWeek() - 1];
}
