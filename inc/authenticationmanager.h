#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <QObject>

#ifdef PLATFORM_ARM
    #include <glassesDevices/fingerprintsensor.h>
#endif

class AuthenticationManager : public QObject
{
    Q_OBJECT
public:
    AuthenticationManager();

private:
#ifdef PLATFORM_ARM
    FingerprintSensor fingerprintSensor;
#endif

signals:
    void unlock();

public slots:
};

#endif // AUTHENTICATIONMANAGER_H
