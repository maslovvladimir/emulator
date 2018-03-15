#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H

#include <QObject>
#include <QString>

class ServerStatePresenter : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString stateText READ stateText NOTIFY stateTextChanged)
    Q_PROPERTY(bool startButtonEnabled READ startButtonEnabled NOTIFY startEnabledChanged)
    Q_PROPERTY(bool stopButtonEnabled READ stopButtonEnabled NOTIFY stopEnabledChanged)
    Q_PROPERTY(QString clientsCountText READ clientsCountText NOTIFY clientsCountTextChanged)
public:
    ServerStatePresenter() = default;
    ServerStatePresenter(const ServerStatePresenter &) = delete;
    ServerStatePresenter& operator=(const ServerStatePresenter &) = delete;
    ~ServerStatePresenter() = default;

    QString stateText() noexcept;
    bool startButtonEnabled() noexcept;
    bool stopButtonEnabled() noexcept;
    QString clientsCountText() noexcept;
    Q_INVOKABLE void onStartClicked() noexcept;
    Q_INVOKABLE void onStopClicked() noexcept;

signals:
    void stateTextChanged();
    void startEnabledChanged();
    void stopEnabledChanged();
    void clientsCountTextChanged();

private:
    bool serverEnabled{false};
    std::size_t clientsCount;    

    void setServerEnabled(bool is_enabled) noexcept;
    void setClientsCount(std::size_t count) noexcept;
};

#endif // SERVER_MODEL_H
