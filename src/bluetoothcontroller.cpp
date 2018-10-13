#include "bluetoothcontroller.h"
#include <smsmanager.h>
#include <QDebug>
#include <QtGlobal>

BluetoothController::BluetoothController()
    : deviceDiscoveryAgent(new QBluetoothDeviceDiscoveryAgent())
{
    deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(3000);
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
    bool timeServiceDiscovered = false;
    bool messageServiceDiscovered = false;
    for (auto& uuid : device.serviceUuids())
    {
        if (uuid == QBluetoothUuid::CurrentTimeService)
        {
            timeServiceDiscovered = true;
        }
        else if (uuid == QBluetoothUuid(SmsManager::getServiceUuid()))
        {
            messageServiceDiscovered = true;
        }
    }
    if (messageServiceDiscovered)
    {
        deviceInfo = device;
        qWarning() << "Found device\n";
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

void BluetoothController::deviceConnected()
{
    connect(controller.get(), &QLowEnergyController::serviceDiscovered, this,
            &BluetoothController::serviceDiscovered);
    connect(controller.get(), &QLowEnergyController::discoveryFinished, this,
            &BluetoothController::serviceScanDone);
    controller->discoverServices();
}

void BluetoothController::serviceScanDone()
{
    if (std::find(serviceUuids.begin(), serviceUuids.end(),
                  QBluetoothUuid::CurrentTimeService) == serviceUuids.end())
    {
        qWarning() << "No current time service discovered!\n";
    }
    else if (std::find(serviceUuids.begin(), serviceUuids.end(),
                       QBluetoothUuid(SmsManager::getServiceUuid())) == serviceUuids.end())
    {
        qWarning() << "No message service discovered!\n";
    }
    else
    {
        qWarning() << "Current time and message service discovered!\n";

        messageService.reset(controller->createServiceObject(QBluetoothUuid(SmsManager::getServiceUuid()), this));
        if(messageService)
        {
            connect(messageService.get(), &QLowEnergyService::stateChanged, this,
                    &BluetoothController::messageServiceDetailScanStatus);
            connect(messageService.get(), &QLowEnergyService::characteristicChanged, this,
                    &BluetoothController::messageCharacteristicChanged);
            connect(messageService.get(), &QLowEnergyService::characteristicRead, this,
                    &BluetoothController::messageCharacteristicRead);
            messageService->discoverDetails();
        }
    }
}

void BluetoothController::timeCharacteristicRead(const QLowEnergyCharacteristic& info,
                                             const QByteArray& value)
{
    qWarning() << "Reading time characteristic\n";
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

void BluetoothController::timeServiceDetailScanStatus(QLowEnergyService::ServiceState newState)
{
    if(newState == QLowEnergyService::ServiceDiscovered)
    {
        qWarning() << "Time Service detail scan\n";
        auto characteristic = timeService->characteristic(QBluetoothUuid::CurrentTime);
        if(!characteristic.isValid()) qWarning() << "time characteristic not valid!\n";
        timeService->readCharacteristic(characteristic);
    }
}

void BluetoothController::messageCharacteristicChanged(const QLowEnergyCharacteristic &characteristic,
                                                       const QByteArray &newValue)
{
    qWarning() << "NEW MESSAGE: ";
    if(characteristic.uuid() == QBluetoothUuid(SmsManager::getMessageUuid()))
    {
        QString text = QString(newValue);
        qWarning() << text << '\n';
    }
}

void BluetoothController::messageCharacteristicRead(const QLowEnergyCharacteristic& info,
                                             const QByteArray& value)
{
    qWarning() << "Reading message characteristic\n";
    if (info.uuid() == QBluetoothUuid(SmsManager::getMessageUuid()))
    {
        qWarning() << "data: " << QString(value);
    }
}

void BluetoothController::messageServiceDetailScanStatus(QLowEnergyService::ServiceState newState)
{
    if(newState == QLowEnergyService::ServiceDiscovered)
    {
        qWarning() << "Message Service detail scan\n";
        auto characteristic = messageService->characteristic(QBluetoothUuid(SmsManager::getMessageUuid()));
        auto descriptor = characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if(!descriptor.isValid()) qWarning() << "message descriptor not valid!\n";
        messageService->writeDescriptor(descriptor, QByteArray::fromHex("0100"));
        if(!characteristic.isValid()) qWarning() << "message characteristic not valid!\n";

        timeService.reset(controller->createServiceObject(QBluetoothUuid::CurrentTimeService, this));
        if(timeService)
        {
            connect(timeService.get(), &QLowEnergyService::stateChanged, this,
                    &BluetoothController::timeServiceDetailScanStatus);
            connect(timeService.get(), &QLowEnergyService::characteristicRead, this,
                    &BluetoothController::timeCharacteristicRead);
            timeService->discoverDetails();
        }

//        messageService->readCharacteristic(characteristic);
    }
}

void BluetoothController::disconnectDevice()
{

}
