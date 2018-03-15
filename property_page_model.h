#ifndef PROPERTY_PAGE_MODEL_H
#define PROPERTY_PAGE_MODEL_H

#include <QObject>

class PropertyPageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool brainbitVisible READ brainbitVisible NOTIFY brainbitVisibleChanged)
    Q_PROPERTY(bool callibriCommonVisible READ callibriCommonVisible NOTIFY callibriCommonVisibleChanged)
    Q_PROPERTY(bool callibriSignalVisible READ callibriSignalVisible NOTIFY callibriSignalVisibleChanged)
public:
    explicit PropertyPageModel(QObject *parent = nullptr);
    PropertyPageModel(const PropertyPageModel &) = delete;
    PropertyPageModel& operator=(const PropertyPageModel &) = delete;

    void setBrainbitVisible(bool);
    void setCallibriCommonVisible(bool);
    void setCallibriSignalVisible(bool);

    bool brainbitVisible() const;
    bool callibriCommonVisible() const;
    bool callibriSignalVisible() const;

signals:
    void brainbitVisibleChanged();
    void callibriCommonVisibleChanged();
    void callibriSignalVisibleChanged();

public slots:

private:
    bool isBrainbitVisible{false};
    bool isCallibriCommonVisible{false};
    bool isCallibriSignalVisible{false};
};

#endif // PROPERTY_PAGE_MODEL_H
