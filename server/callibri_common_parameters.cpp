#include "callibri_common_parameters.h"

namespace Nes
{

Byte CallibriCommonParameters::getModuleFlags() const noexcept {
    return 0x01;
}

void CallibriCommonParameters::setModuleFlags(Byte flags) noexcept {
    moduleFlags = flags;
}

SamplingFrequency CallibriCommonParameters::getSamplingFrequency() const noexcept {
    return samplingFrequency;
}

void CallibriCommonParameters::setSamplingFrequency(SamplingFrequency freq) noexcept {
    samplingFrequency = freq;
    if(samplingFreqChangedCallback) samplingFreqChangedCallback();
}

void CallibriCommonParameters::setSamplingFreqChangedCallback(std::function<void ()> callback){
    samplingFreqChangedCallback = callback;
}

ExtSwitchState CallibriCommonParameters::getExtSwitchState() const noexcept {
    return extSwitchState;
}

void CallibriCommonParameters::setExtSwitchState(ExtSwitchState state) noexcept {
    extSwitchState = state;
    if (extSwitchStateChangedCallback) extSwitchStateChangedCallback();
}

void CallibriCommonParameters::setSwitchStateCallback(std::function<void ()> callback) {
    extSwitchStateChangedCallback = callback;
}

Gain CallibriCommonParameters::getGain() const noexcept {
    return gain;
}

void CallibriCommonParameters::setGain(Gain g) noexcept {
    gain = g;
    if (gainChangedCallback) gainChangedCallback();
}

void CallibriCommonParameters::setGainChangedCallback(std::function<void ()> callback){
    gainChangedCallback = callback;
}

int CallibriCommonParameters::getOffset() const noexcept {
    return offset;
}

void CallibriCommonParameters::setOffset(int off) noexcept {
    offset = off;
    if (offsetChangedCallback) offsetChangedCallback();
}

void CallibriCommonParameters::setOffsetChangedCallback(std::function<void ()> callback){
    hpfStateChangedCallback = callback;
}

AdcInputState CallibriCommonParameters::getAdcInputState() const noexcept {
    return adcInputState;
}

bool CallibriCommonParameters::getHpfState() const noexcept {
    return isHpfEnabled;
}

void CallibriCommonParameters::setHpfState(bool state) noexcept {
    isHpfEnabled = state;
    if (hpfStateChangedCallback) hpfStateChangedCallback();
}

void CallibriCommonParameters::setHpfStateCallback(std::function<void ()> callback){
    hpfStateChangedCallback = callback;
}

void CallibriCommonParameters::setAdcInputState(AdcInputState state) noexcept {
    adcInputState = state;
    if (adcInputStateChangedCallback) adcInputStateChangedCallback();
}

void CallibriCommonParameters::setAdcInputStateCallback(std::function<void ()> callback){
    adcInputStateChangedCallback = callback;
}

}
