#ifndef CALLIBRI_COMMON_PARAMETERS_H
#define CALLIBRI_COMMON_PARAMETERS_H

#include "nes_types.h"
#include <functional>

namespace Nes
{

enum class SamplingFrequency : int{
    Hz125 = 0,
    Hz250 = 1,
    Hz500 = 2,
    Hz1000 = 3,
    Hz2000 = 4,
    Hz4000 = 5,
    Hz8000 = 6
};

inline int getSamplingFrequencyValue(SamplingFrequency code){
    switch(code){
    case SamplingFrequency::Hz125:
        return 125;
    case SamplingFrequency::Hz250:
        return 250;
    case SamplingFrequency::Hz500:
        return 500;
    case SamplingFrequency::Hz1000:
        return 1000;
    case SamplingFrequency::Hz2000:
        return 2000;
    case SamplingFrequency::Hz4000:
        return 4000;
    case SamplingFrequency::Hz8000:
        return 8000;
    default:
        return 0;
    }
}

enum class Gain : int{
    Gain1 = 0,
    Gain2 = 1,
    Gain3 = 2,
    Gain4 = 3,
    Gain6 = 4,
    Gain8 = 5,
    Gain12 = 6
};

inline int getGainValue(Gain code){
    switch(code){
    case Gain::Gain1:
        return 1;
    case Gain::Gain2:
        return 2;
    case Gain::Gain3:
        return 3;
    case Gain::Gain4:
        return 4;
    case Gain::Gain6:
        return 6;
    case Gain::Gain8:
        return 8;
    case Gain::Gain12:
        return 12;
    default:
        return 0;
    }
}

enum class ExtSwitchState : int {
    MioElectrodesRespUSB = 0,
    MioElectrodes = 1,
    MioUSB = 2,
    RespUSB = 3
};

enum class AdcInputState : int {
    Electrodes = 0,
    Short = 1,
    Test = 2,
    Resistance = 3
};

class CallibriCommonParameters{
public:
    Byte getModuleFlags() const noexcept;
    void setModuleFlags(Byte) noexcept;
    SamplingFrequency getSamplingFrequency() const noexcept;
    void setSamplingFrequency(SamplingFrequency) noexcept;
    void setSamplingFreqChangedCallback(std::function<void()>);
    ExtSwitchState getExtSwitchState() const noexcept;
    void setExtSwitchState(ExtSwitchState) noexcept;
    void setSwitchStateCallback(std::function<void(void)>);
    Gain getGain() const noexcept;
    void setGain(Gain) noexcept;
    void setGainChangedCallback(std::function<void()>);
    int getOffset() const noexcept;
    void setOffset(int) noexcept;
    void setOffsetChangedCallback(std::function<void()>);
    AdcInputState getAdcInputState() const noexcept;
    bool getHpfState() const noexcept;
    void setHpfState(bool state) noexcept;
    void setHpfStateCallback(std::function<void()>);
    void setAdcInputState(AdcInputState) noexcept;
    void setAdcInputStateCallback(std::function<void()>);

private:
    ExtSwitchState extSwitchState{ExtSwitchState::MioElectrodesRespUSB};
    std::function<void(void)> extSwitchStateChangedCallback;
    Byte moduleFlags{0x00};
    SamplingFrequency samplingFrequency{SamplingFrequency::Hz250};
    std::function<void()> samplingFreqChangedCallback;
    Gain gain{Gain::Gain6};
    std::function<void()> gainChangedCallback;
    int offset{0};
    std::function<void()> offsetChangedCallback;
    AdcInputState adcInputState{AdcInputState::Resistance};
    std::function<void()> adcInputStateChangedCallback;
    bool isHpfEnabled{true};
    std::function<void()> hpfStateChangedCallback;
};

}

#endif // CALLIBRI_COMMON_PARAMETERS_H
