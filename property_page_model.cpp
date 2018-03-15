#include "property_page_model.h"

PropertyPageModel::PropertyPageModel(QObject *parent) : QObject(parent) {

}

void PropertyPageModel::setBrainbitVisible(bool is_visible){
    isBrainbitVisible = is_visible;
    emit brainbitVisibleChanged();
}

void PropertyPageModel::setCallibriCommonVisible(bool is_visible){
    isCallibriCommonVisible = is_visible;
    emit callibriCommonVisibleChanged();
}

void PropertyPageModel::setCallibriSignalVisible(bool is_visible){
    isCallibriSignalVisible = is_visible;
    emit callibriSignalVisibleChanged();
}

bool PropertyPageModel::brainbitVisible() const {
    return isBrainbitVisible;
}

bool PropertyPageModel::callibriCommonVisible() const {
    return isCallibriCommonVisible;
}

bool PropertyPageModel::callibriSignalVisible() const{
    return isCallibriSignalVisible;
}
