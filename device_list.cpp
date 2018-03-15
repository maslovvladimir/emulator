#include "device_list.h"
#include "callibri_impl.h"
#include "brainbit_impl.h"

DeviceList::DeviceList(PropertyPageModel *page_model,
                       CallibriCommonModel *callibri_common,
                       CallibriSignalModel *callibri_signal,
                       QObject *parent) :
    QObject(parent),
    pageModel(page_model),
    callibriCommonModel(callibri_common),
    callibriSignalModel(callibri_signal){
    deviceItems.push_back(std::make_shared<UiDevice>(getImpl(DeviceType::Callibri)));
    deviceItems.push_back(std::make_shared<UiDevice>(getImpl(DeviceType::Brainbit)));
}

std::weak_ptr<UiDevice> DeviceList::operator[](int index){
    return deviceItems[index];
}

auto DeviceList::begin() -> iterator{
    return deviceItems.begin();
}

auto DeviceList::end() -> iterator{
    return deviceItems.end();
}

int DeviceList::size(){
    return static_cast<int>(deviceItems.size());
}

std::unique_ptr<UiDeviceImpl> DeviceList::getImpl(DeviceType type){
    return (type == DeviceType::Brainbit) ?
                std::unique_ptr<UiDeviceImpl>(new BrainbitImpl()) :
                std::unique_ptr<UiDeviceImpl>(new CallibriImpl(callibriCommonModel, callibriSignalModel));
}

void DeviceList::appendItem(){
    emit preItemAppended();
    deviceItems.push_back(std::make_shared<UiDevice>(getImpl(DeviceType::Callibri)));
    emit postItemAppended();
}

void DeviceList::removeItem(int index){
    emit preItemRemoved(index);

    deviceItems.erase(deviceItems.begin()+index);

    emit postItemRemoved();
}

void DeviceList::selectItem(int index, int moduleCode){
    auto selectedDevice = deviceItems[index];
    selectedDevice->activate();
    if(selectedDevice->getType() == DeviceType::Brainbit){
        pageModel->setBrainbitVisible(true);
        pageModel->setCallibriSignalVisible(false);
        pageModel->setCallibriCommonVisible(false);
    }
    else{
        auto module = static_cast<DeviceModule>(moduleCode);
        pageModel->setBrainbitVisible(false);
        switch(module){
        case DeviceModule::Main:{
            pageModel->setCallibriSignalVisible(false);
            pageModel->setCallibriCommonVisible(true);
            break;
        }
        case DeviceModule::Signal:{
            pageModel->setCallibriSignalVisible(true);
            pageModel->setCallibriCommonVisible(false);
            break;
        }
        default:{
            pageModel->setCallibriSignalVisible(false);
            pageModel->setCallibriCommonVisible(false);
            break;
        }
        }
    }
}
