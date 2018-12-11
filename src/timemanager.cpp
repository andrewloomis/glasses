#include "timemanager.h"
#include <iostream>

TimeManager::TimeManager(QObject *parent)
    : QObject(parent), mTime(QDate(0,0,2), QTime(0,0,0))
{

}

QString TimeManager::getDateString() const
{
    auto day = daysOfWeek[static_cast<std::size_t>(mTime.date().dayOfWeek() - 1)];
    auto month = months[static_cast<std::size_t>(mTime.date().month() - 1)];
    auto number = QString::number(mTime.date().day());
    return day + ", " + month + ' ' + number;
}

QString TimeManager::getTimeString() const
{
    int mins = mTime.time().minute();
    return QString::number(mTime.time().hour() % 12)
            + ((mins > 9) ? ":" : ":0") + QString::number(mins);
}
