#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <QtBluetooth>
#include <memory>

class BluetoothController : public QObject
{
    Q_OBJECT
public:
    BluetoothController();

private:
    std::unique_ptr<QBluetoothDeviceDiscoveryAgent> deviceDiscoveryAgent = nullptr;
    std::unique_ptr<QLowEnergyController> controller = nullptr;
    std::unique_ptr<QLowEnergyService> timeService = nullptr;
    QBluetoothDeviceInfo deviceInfo;
    std::vector<QBluetoothUuid> serviceUuids;

    void foundDevice(const QBluetoothDeviceInfo &device);
    void serviceDiscovered(const QBluetoothUuid &serviceUuid);
    void serviceScanDone();
    void serviceDetailScanStatus(QLowEnergyService::ServiceState newState);
    void characteristicRead(const QLowEnergyCharacteristic& info, const QByteArray& value);
    void deviceConnected();
    void scanFinished();
    void disconnectDevice();

signals:
    void newTime(QDate date, QTime time);
};

#endif // BLUETOOTHCONTROLLER_H
