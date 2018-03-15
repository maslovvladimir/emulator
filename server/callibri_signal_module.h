#ifndef CALLIBRI_SIGNAL_MODULE_H
#define CALLIBRI_SIGNAL_MODULE_H

#include "callibri_generic_module.h"
#include "signal_generator.h"
#include "nes_types.h"
#include <chrono>

namespace Nes
{

using CallibriSignalBaseModule = CallibriGenericModule<
CallibriCommandCode::START_ADC_DATA_THROW,
CallibriCommandCode::STOP_ADC_DATA_THROW,
CallibriCommandCode::SET_FSAM,
CallibriCommandCode::SET_DATA_OFFSET,
CallibriCommandCode::SET_PGA_GAIN,
CallibriCommandCode::GET_ELECTRODE_STATE,
CallibriCommandCode::SWITCH_ADC_INP,
CallibriCommandCode::SWITCH_FILTER_STATE>;

class CallibriSignalModule : public CallibriSignalBaseModule {
public:
    CallibriSignalModule(std::shared_ptr<CallibriCommonParameters>, std::shared_ptr<SignalGenerator>) noexcept;
    ~CallibriSignalModule() = default;

    SamplingFrequency getSamplingFrequency() const noexcept;
    void setSamplingFrequency(SamplingFrequency) noexcept;
    void setSamplingFrequencyChangedCallback(std::function<void()>) noexcept;
    Gain getGain() const noexcept;
    void setGain(Gain) noexcept;
    void setGainChangedCallback(std::function<void()>) noexcept;
    AdcInputState getAdcInputState() const noexcept;
    void setAdcInputState(AdcInputState) noexcept;
    void setAdcInputStateChangedCallback(std::function<void()>) noexcept;

private:
    std::shared_ptr<SignalGenerator> signalGenerator;
    ByteBuffer sendBuffer;
    unsigned short packetNumber{0};
    bool isSignalThrowing{false};
    std::chrono::time_point<std::chrono::high_resolution_clock> signalStartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastSendTime;

    void doWork() noexcept override;
    void handleCommand(const CallibriCommand &)noexcept override;
    void onStartDataThrowCommand();
    void onStopDataThrowCommand();
    void onSetFSamplingCommand(CallibriCommand);
    void onSetOffsetCommand(CallibriCommand);
    void onSetGainCommand(CallibriCommand);
    void onGetElectrodeStateCommand(CallibriCommand);
    void onSetAdcInputCommand(CallibriCommand);
    void onSetFilterStateCommand(CallibriCommand);
    void onUnknownCommand() noexcept;
    ByteBuffer getAdcSamples(std::vector<double>);
};

}

#endif // CALLIBRI_SIGNAL_MODULE_H
