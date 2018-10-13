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
    Q_PROPERTY(QString timeString READ getTimeString)
    Q_PROPERTY(QString dateString READ getDateString)
public:
    explicit TimeManager(QObject *parent = nullptr);

private:
    QDateTime mTime;
    const std::array<QString, 7> daysOfWeek = {"Mon", "Tues", "Wed",
                                      "Thurs", "Fri", "Sat", "Sun"};
    const std::array<QString, 12> months = {"Jan", "Feb", "Mar",
                                      "Apr", "May", "Jun", "Jul",
                                           "Aug", "Sep", "Oct",
                                           "Nov", "Dec"};

    QString getTimeString() const;
    QString getDateString() const;

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
