#include "callibri_signal_module.h"
#include "callibri_data_packet.h"
#include <iostream>

Nes::CallibriSignalModule::CallibriSignalModule(std::shared_ptr<Nes::CallibriCommonParameters> common_params,
                                                std::shared_ptr<SignalGenerator> generator) noexcept :
    CallibriSignalBaseModule(common_params),
    signalGenerator(generator){

}

Nes::SamplingFrequency Nes::CallibriSignalModule::getSamplingFrequency() const noexcept {
    return commonParameters->getSamplingFrequency();
}

void Nes::CallibriSignalModule::setSamplingFrequency(Nes::SamplingFrequency frequency) noexcept {
    commonParameters->setSamplingFrequency(frequency);
}

void Nes::CallibriSignalModule::setSamplingFrequencyChangedCallback(std::function<void ()> callback) noexcept {
    commonParameters->setSamplingFreqChangedCallback(callback);
}

Nes::Gain Nes::CallibriSignalModule::getGain() const noexcept {
    return commonParameters->getGain();
}

void Nes::CallibriSignalModule::setGain(Nes::Gain gain) noexcept {
    commonParameters->setGain(gain);
}

void Nes::CallibriSignalModule::setGainChangedCallback(std::function<void ()> callback) noexcept {
    commonParameters->setGainChangedCallback(callback);
}

Nes::AdcInputState Nes::CallibriSignalModule::getAdcInputState() const noexcept {
    return commonParameters->getAdcInputState();
}

void Nes::CallibriSignalModule::setAdcInputState(Nes::AdcInputState state) noexcept {
    commonParameters->setAdcInputState(state);
}

void Nes::CallibriSignalModule::setAdcInputStateChangedCallback(std::function<void ()> callback) noexcept {
    commonParameters->setAdcInputStateCallback(callback);
}

void Nes::CallibriSignalModule::doWork() noexcept {
    if (!isSignalThrowing)
        return;

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - lastSendTime;
    auto frequency = getSamplingFrequencyValue(commonParameters->getSamplingFrequency());
    auto startSample = (lastSendTime - signalStartTime).count() * frequency;
    auto length = elapsed.count() * frequency;
    if (length > 0){
        lastSendTime = now;
        auto data = signalGenerator->generateUv(startSample, length, frequency);
        auto adcSamples = getAdcSamples(data);
        std::copy(adcSamples.begin(), adcSamples.end(), std::back_inserter(sendBuffer));
    }
    while(sendBuffer.size()>=18){
        CallibriDataPacket packet(packetNumber);
        packetNumber++;
        std::copy(sendBuffer.begin(), sendBuffer.begin()+18, packet.data().begin());
        pushResponse(packet);
        sendBuffer.erase(sendBuffer.begin(), sendBuffer.begin()+18);
    }
}

void Nes::CallibriSignalModule::handleCommand(const Nes::CallibriCommand &command) noexcept {
    switch(command.code()){
    case CallibriCommandCode::START_ADC_DATA_THROW:{
        onStartDataThrowCommand();
        break;
    }
    case CallibriCommandCode::STOP_ADC_DATA_THROW:{
        onStopDataThrowCommand();
        break;
    }
    case CallibriCommandCode::SET_FSAM:{
        onSetFSamplingCommand(command);
        break;
    }
    case CallibriCommandCode::SET_DATA_OFFSET:{
        onSetOffsetCommand(command);
        break;
    }
    case CallibriCommandCode::SET_PGA_GAIN:{
        onSetGainCommand(command);
        break;
    }
    case CallibriCommandCode::GET_ELECTRODE_STATE:{
        onGetElectrodeStateCommand(command);
        break;
    }
    case CallibriCommandCode::SWITCH_ADC_INP:{
        onSetAdcInputCommand(command);
        break;
    }
    case CallibriCommandCode::SWITCH_FILTER_STATE:{
        onSetFilterStateCommand(command);
        break;
    }
    default: {
        onUnknownCommand();
    }
    }
}

void Nes::CallibriSignalModule::onStartDataThrowCommand(){
    if (!isSignalThrowing){
        isSignalThrowing = true;
        signalStartTime = std::chrono::high_resolution_clock::now();
        lastSendTime = signalStartTime;
        packetNumber = 0;
    }
    pushResponse(CallibriCommand(CallibriCommandCode::START_ADC_DATA_THROW, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onStopDataThrowCommand(){
    isSignalThrowing = false;
    pushResponse(CallibriCommand(CallibriCommandCode::STOP_ADC_DATA_THROW, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onSetFSamplingCommand(Nes::CallibriCommand command){
    auto fSamplingCode = command.data()[0];
    if (fSamplingCode > 6){
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_WRONG_PARAM, 0xA5B6C7));
        return;
    }
    commonParameters->setSamplingFrequency(static_cast<SamplingFrequency>(fSamplingCode));
    pushResponse(CallibriCommand(CallibriCommandCode::SET_FSAM, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onSetOffsetCommand(Nes::CallibriCommand command){
    commonParameters->setOffset(static_cast<int>(command.data()[0]));
    pushResponse(CallibriCommand(CallibriCommandCode::SET_DATA_OFFSET, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onSetGainCommand(Nes::CallibriCommand command){
    auto gainCode = command.data()[0];
    if (gainCode > 6){
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_WRONG_PARAM, 0xA5B6C7));
        return;
    }
    commonParameters->setGain(static_cast<Gain>(gainCode));
    pushResponse(CallibriCommand(CallibriCommandCode::SET_FSAM, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onGetElectrodeStateCommand(Nes::CallibriCommand command){
    CallibriCommand electrodeStateResponse(CallibriCommandCode::GET_ELECTRODE_STATE, CallibriErrorCode::NO_ERROR, 0xA5B6C7);
    electrodeStateResponse.data()[0] = 0;
    pushResponse(electrodeStateResponse);
}

void Nes::CallibriSignalModule::onSetAdcInputCommand(Nes::CallibriCommand command){
    auto adcInputCode = command.data()[0];
    if (adcInputCode > 3){
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_WRONG_PARAM, 0xA5B6C7));
        return;
    }
    commonParameters->setAdcInputState(static_cast<AdcInputState>(adcInputCode));
    pushResponse(CallibriCommand(CallibriCommandCode::SWITCH_ADC_INP, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onSetFilterStateCommand(Nes::CallibriCommand command){
    auto filterStateCode = command.data()[0];
    if (filterStateCode > 1){
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_WRONG_PARAM, 0xA5B6C7));
        return;
    }
    commonParameters->setHpfState(static_cast<bool>(filterStateCode));
    pushResponse(CallibriCommand(CallibriCommandCode::SWITCH_FILTER_STATE, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void Nes::CallibriSignalModule::onUnknownCommand() noexcept {
    pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_NO_CMD, 0xA5B6C7));
}

Net::ByteBuffer Nes::CallibriSignalModule::getAdcSamples(std::vector<double> samplesUv){
    auto gain = getGainValue(commonParameters->getGain());
    Net::ByteBuffer result;
    for (auto& sample : samplesUv){
        auto adcSample = (sample / 1000.0) * gain * 8388607 / 2.42;
        if (adcSample > std::numeric_limits<short>::max())
            adcSample =  std::numeric_limits<short>::max();
        else if (adcSample <  std::numeric_limits<short>::min())
            adcSample =  std::numeric_limits<short>::min();
        auto shortSample = static_cast<short>(adcSample);
        ByteInterpreter<short> sampleBytes;
        sampleBytes.value = shortSample;
        result.push_back(sampleBytes.bytes[0]);
        result.push_back(sampleBytes.bytes[1]);
    }
    return result;
}
