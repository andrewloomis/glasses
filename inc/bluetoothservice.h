#ifndef BLUETOOTHSERVICE_H
#define BLUETOOTHSERVICE_H

#include <QtBluetooth>

class BluetoothService
{
public:

    struct ServiceType
    {
        QBluetoothUuid serviceUuid;
        QBluetoothUuid characteristicUuid;
        int valueSize = 0;

        template<typename T>
        void setValueSize()
        {
            valueSize = sizeof (T);
        }
    };

    BluetoothService(QSharedPointer<QLowEnergyController> controller);
    void defaultSetup(ServiceType& serviceType);
    void update(QByteArray value);

private:
    QSharedPointer<QLowEnergyController> mController;
    QPointer<QLowEnergyService> service;
    QLowEnergyServiceData serviceData;
    QLowEnergyCharacteristicData charData;
    QLowEnergyDescriptorData clientConfig;
};

#endif // BLUETOOTHSERVICE_H
