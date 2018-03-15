#include "server_presenter.h"

QString ServerStatePresenter::stateText() noexcept {
    return serverEnabled ? "Enabled" : "Disabled";
}

bool ServerStatePresenter::startButtonEnabled() noexcept {
    return !serverEnabled;
}

bool ServerStatePresenter::stopButtonEnabled() noexcept {
    return serverEnabled;
}

QString ServerStatePresenter::clientsCountText() noexcept {
    return QString::number(clientsCount);
}

void ServerStatePresenter::onStartClicked() noexcept {
    setServerEnabled(true);
}

void ServerStatePresenter::onStopClicked() noexcept {
    setServerEnabled(false);
}

void ServerStatePresenter::setServerEnabled(bool is_enabled) noexcept {
    if (serverEnabled == is_enabled)
        return;

    serverEnabled = is_enabled;
    emit stateTextChanged();
    emit startEnabledChanged();
    emit stopEnabledChanged();
}

void ServerStatePresenter::setClientsCount(std::size_t count) noexcept {
    if (clientsCount == count)
        return;

    clientsCount = count;
    emit clientsCountTextChanged();
}
