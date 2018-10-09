#ifndef BLUETOOTHSERVICE_H
#define BLUETOOTHSERVICE_H

#include <QtBluetooth>
#include <memory>

class BluetoothService
{
public:

    struct ServiceType
    {
        QBluetoothUuid serviceUuid;
        QBluetoothUuid characteristicUuid;
        QLowEnergyCharacteristic::PropertyTypes properties;
        int valueSize = 0;

        template<typename T>
        void setValueSize()
        {
            valueSize = sizeof (T);
        }
    };

    BluetoothService(std::shared_ptr<QLowEnergyController> controller);
    void defaultSetup(ServiceType& serviceType);
    void update(QByteArray value);

private:
    std::shared_ptr<QLowEnergyController> mController;
    std::unique_ptr<QLowEnergyService> service;
    QLowEnergyServiceData serviceData;
    QLowEnergyCharacteristicData charData;
    QLowEnergyDescriptorData clientConfig;
};

#endif // BLUETOOTHSERVICE_H
