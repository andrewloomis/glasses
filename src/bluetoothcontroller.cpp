#include "bluetoothcontroller.h"
#include <QDebug>

BluetoothController::BluetoothController()
    : deviceDiscoveryAgent(new QBluetoothDeviceDiscoveryAgent())
{
    deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(deviceDiscoveryAgent.get(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothController::foundDevice);
    connect(deviceDiscoveryAgent.get(), &QBluetoothDeviceDiscoveryAgent::finished, this,
            &BluetoothController::scanFinished);
    connect(deviceDiscoveryAgent.get(), &QBluetoothDeviceDiscoveryAgent::canceled, this,
            &BluetoothController::scanFinished);
    deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BluetoothController::foundDevice(const QBluetoothDeviceInfo &device)
{
    if(device.name() == "Glasses")
    {
        qWarning() << "Found device\n";
        deviceInfo = device;
    }
}

void BluetoothController::serviceDiscovered(const QBluetoothUuid &serviceUuid)
{
    serviceUuids.push_back(serviceUuid);
    qWarning() << "Service discovered: " << serviceUuid.toString() << '\n';
}

void BluetoothController::scanFinished()
{
    if (deviceInfo.isValid())
    {
        if (controller)
        {
            qWarning() << "Controller already exists, killing it\n";
            controller->disconnectFromDevice();
            controller.release();
            controller = nullptr;
        }

        controller = std::make_unique<QLowEnergyController>(deviceInfo);
        connect(controller.get(), &QLowEnergyController::connected, this,
                &BluetoothController::deviceConnected);
        controller->connectToDevice();
    }
}

void BluetoothController::serviceScanDone()
{
    if (std::find(serviceUuids.begin(), serviceUuids.end(),
                  QBluetoothUuid::CurrentTimeService) == serviceUuids.end())
    {
        qWarning() << "No current time service discovered!\n";
    }
    else
    {
        qWarning() << "Current time service discovered!\n";
        timeService.reset(controller->createServiceObject(QBluetoothUuid::CurrentTimeService, this));
        if(timeService)
        {
            connect(timeService.get(), &QLowEnergyService::stateChanged, this,
                    &BluetoothController::serviceDetailScanStatus);
            connect(timeService.get(), &QLowEnergyService::characteristicRead, this,
                    &BluetoothController::characteristicRead);
            timeService->discoverDetails();
        }

    }
}

void BluetoothController::characteristicRead(const QLowEnergyCharacteristic& info,
                                             const QByteArray& value)
{
    if (info.uuid() == QBluetoothUuid::CurrentTime && value.length() == 10)
    {
        QDate date(value[1] << 8 | value[0], value[2], value[3]);
        QTime time(value[4], value[5], value[6], (value[8]/256) * 1000);
        qWarning() << "New DateTime: " << time.hour() << ':' << time.minute()
                   << ' ' << date.dayOfWeek() << ", " << date.month()
                   << ' ' << date.day() << ", " << date.year();
        emit newTime(date, time);
    }
}


void BluetoothController::serviceDetailScanStatus(QLowEnergyService::ServiceState newState)
{
    if(newState == QLowEnergyService::ServiceDiscovered)
    {
        auto characteristic = timeService->characteristic(QBluetoothUuid::CurrentTime);
        if(!characteristic.isValid()) qWarning() << "characteristic not valid!\n";
        timeService->readCharacteristic(characteristic);
    }
}

void BluetoothController::deviceConnected()
{
    connect(controller.get(), &QLowEnergyController::serviceDiscovered, this,
            &BluetoothController::serviceDiscovered);
    connect(controller.get(), &QLowEnergyController::discoveryFinished, this,
            &BluetoothController::serviceScanDone);
    controller->discoverServices();
}

void BluetoothController::disconnectDevice()
{

}
