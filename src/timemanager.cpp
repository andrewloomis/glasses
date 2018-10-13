#include "timemanager.h"
#include <iostream>

TimeManager::TimeManager(QObject *parent)
    : QObject(parent), mTime(QDate(0,0,2), QTime(0,0,0))
{

}

QString TimeManager::getDateString() const
{
    return daysOfWeek[(std::size_t)mTime.date().dayOfWeek() - 1]
            + ", " + months[(std::size_t)mTime.date().month() - 1]
            + ' ' + QString::number(mTime.date().day());
}

QString TimeManager::getTimeString() const
{
    int mins = mTime.time().minute();
    return QString::number(mTime.time().hour() % 12)
            + ((mins > 9) ? ":" : ":0") + QString::number(mins);
}
