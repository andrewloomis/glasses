#include "bluetoothservice.h"

BluetoothService::BluetoothService(QSharedPointer<QLowEnergyController> controller)
    : mController(controller)
{

}

void BluetoothService::defaultSetup(ServiceType& serviceType)
{
    charData.setUuid(serviceType.characteristicUuid);
    charData.setValue(QByteArray(serviceType.valueSize, 0));
    charData.setProperties(QLowEnergyCharacteristic::Notify);
    // Characteristic descriptor
    clientConfig = QLowEnergyDescriptorData(QBluetoothUuid::ClientCharacteristicConfiguration,
                                                QByteArray(2, 0));
    charData.addDescriptor(clientConfig);

    // Service
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(serviceType.serviceUuid);
    serviceData.addCharacteristic(charData);
    service = mController->addService(serviceData);
}

void BluetoothService::update(QByteArray value)
{
    service->writeCharacteristic(service->characteristic(charData.uuid()), value);
}
