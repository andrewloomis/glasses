#include "bluetoothcontroller.h"
#include <iostream>

BluetoothController::BluetoothController()
    : leController(QLowEnergyController::createPeripheral()),
      batteryService(leController)
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    setupAdvertising();
    setupBatteryLevelService();
    startAdvertising();
}

void BluetoothController::setupAdvertising()
{
    // Advertising visibility and name
    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    advertisingData.setIncludePowerLevel(true);
    advertisingData.setLocalName("SmartGlasses");
    // List of advertised services
    advertisingData.setServices(QList<QBluetoothUuid>() << QBluetoothUuid::BatteryService);
    std::cout << advertisingData.services()[0].data1 << std::endl;
}

void BluetoothController::setupBatteryLevelService()
{
    BluetoothService::ServiceType service;
    service.serviceUuid = QBluetoothUuid(QBluetoothUuid::BatteryService);
    service.characteristicUuid = QBluetoothUuid(QBluetoothUuid::BatteryLevel);
    service.setValueSize<uint8_t>();
    batteryService.defaultSetup(service);
}

void BluetoothController::startAdvertising()
{
    leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData,
                                   advertisingData);
}

void BluetoothController::updateBatteryLevel(uint8_t level)
{
    QByteArray data;
    data.append(level);
    batteryService.update(data);
}
