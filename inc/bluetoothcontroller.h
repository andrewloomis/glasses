#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <QtBluetooth>
#include <bluetoothservice.h>

class BluetoothController
{
public:
    BluetoothController();
    void updateBatteryLevel(uint8_t level);

private:
    const QSharedPointer<QLowEnergyController> leController;
    BluetoothService batteryService;
    QLowEnergyAdvertisingData advertisingData;

    void setupAdvertising();
    void startAdvertising();
    void setupBatteryLevelService();
};

#endif // BLUETOOTHCONTROLLER_H
