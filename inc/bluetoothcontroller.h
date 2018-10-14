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
    std::unique_ptr<QLowEnergyService> messageService = nullptr;
    QBluetoothDeviceInfo deviceInfo;
    std::vector<QBluetoothUuid> serviceUuids;

    void foundDevice(const QBluetoothDeviceInfo &device);
    void serviceDiscovered(const QBluetoothUuid &serviceUuid);
    void serviceScanDone();
    void deviceConnected();
    void scanFinished();
    void disconnectDevice();

    //Time service
    void timeServiceDetailScanStatus(QLowEnergyService::ServiceState newState);
    void timeCharacteristicRead(const QLowEnergyCharacteristic& info, const QByteArray& value);

    // Message service
    void messageServiceDetailScanStatus(QLowEnergyService::ServiceState newState);
    void messageCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void messageCharacteristicRead(const QLowEnergyCharacteristic& info, const QByteArray& value);

signals:
    void newTime(QDate date, QTime time);
    void newMessage(const QString name, const QString body);
};

#endif // BLUETOOTHCONTROLLER_H
