#ifndef CALLIBRI_COMMON_MODEL_H
#define CALLIBRI_COMMON_MODEL_H

#include <QObject>
#include <memory>
#include "server/callibri_main_module.h"


class CallibriCommonModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int firmware READ firmware WRITE setFirmware NOTIFY firmwareChanged)
    Q_PROPERTY(int build READ build WRITE setBuild NOTIFY buildChanged)
    Q_PROPERTY(int radioFreq READ radioFreq WRITE setRadioFreq NOTIFY radioFreqChanged)
    Q_PROPERTY(int extSwitchIndex READ extSwitchIndex WRITE setExtSwitchIndex NOTIFY extSwitchIndexChanged)
    Q_PROPERTY(int batteryVoltage READ batteryVoltage WRITE setBatteryVoltage NOTIFY batteryVoltageChanged)
public:
    explicit CallibriCommonModel(QObject *parent = nullptr);

    void setModule(std::weak_ptr<Nes::CallibriMainModule> common_module);

    int address() const noexcept;
    int firmware() const noexcept;
    int build() const noexcept;
    int radioFreq() const noexcept;
    int extSwitchIndex() const noexcept;
    int batteryVoltage() const noexcept;

    void setAddress(int);
    void setFirmware(int);
    void setBuild(int);
    void setRadioFreq(int);
    void setExtSwitchIndex(int);
    void setBatteryVoltage(int);

signals:
    void addressChanged();
    void firmwareChanged();
    void buildChanged();
    void radioFreqChanged();
    void extSwitchIndexChanged();
    void batteryVoltageChanged();

public slots:

private:
    std::weak_ptr<Nes::CallibriMainModule> modulePtr;

    void emitAll();
};

#endif // CALLIBRI_COMMON_MODEL_H
