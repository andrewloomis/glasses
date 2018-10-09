#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QObject>

class TimeManager : public QObject
{
    Q_OBJECT
public:
    explicit TimeManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TIMEMANAGER_H