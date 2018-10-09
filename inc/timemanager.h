#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QObject>
#include <QDateTime>
#include <string>
#include <QString>
#include <array>

class TimeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dayOfWeek READ getDayOfWeek)
public:
    explicit TimeManager(QObject *parent = nullptr);
    QString getDayOfWeek() const;

private:
    QDateTime mTime;

    const std::array<QString, 7> daysOfWeek = {"Mon", "Tues", "Wed",
                                      "Thurs", "Fri", "Sat", "Sun"};

signals:
    void updateUiTime();

public slots:
    void updateTime(QDate date, QTime time)
    {
        mTime = QDateTime(date, time);
        emit updateUiTime();
    }
};

#endif // TIMEMANAGER_H
