#include "callibri_signal_model.h"

CallibriSignalModel::CallibriSignalModel(QObject *parent) : QObject(parent){

}

void CallibriSignalModel::setModule(std::weak_ptr<Nes::CallibriSignalModule> signal_module){
    modulePtr = signal_module;
    auto module = modulePtr.lock();
    if (module){
        module->setSamplingFrequencyChangedCallback([=](){ emit samplingFrequencyChanged(); });
        module->setGainChangedCallback([=](){ emit gainIndexChanged(); });
        module->setAdcInputStateChangedCallback([=](){ emit adcInputIndexChanged(); });
    }
    emitAll();
}

void CallibriSignalModel::setSineGenerator(std::weak_ptr<SineGenerator> generator){
    sineGeneratorPtr = generator;
    emitAll();
}

int CallibriSignalModel::samplingFrequencyIndex() const {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return static_cast<int>(module->getSamplingFrequency());
}

int CallibriSignalModel::sineAmplitude() const {
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return 0;

    return sineGenerator->getAmplitudeUV();
}

int CallibriSignalModel::sineFrequency() const {
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return 0;

    return sineGenerator->getFrequency();
}

int CallibriSignalModel::sinePhase() const {
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return 0;

    return sineGenerator->getPhase();
}

int CallibriSignalModel::noiseAmplitude() const {
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return 0;

    return noiseAmpl;
}

int CallibriSignalModel::gainIndex() const {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return static_cast<int>(module->getGain());
}

int CallibriSignalModel::adcInputIndex() const {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return static_cast<int>(module->getAdcInputState());
}

void CallibriSignalModel::setSamplingFrequencyIndex(int index) {
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setSamplingFrequency(static_cast<Nes::SamplingFrequency>(index));
    emit samplingFrequencyChanged();
}

void CallibriSignalModel::setSineAmplitude(int amplitude){
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return;

    sineGenerator->setAmplitudeUV(amplitude);
    emit sineAmplitudeChanged();
}

void CallibriSignalModel::setSineFrequency(int frequency){
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return;

    sineGenerator->setFrequency(frequency);
    emit sineFrequencyChanged();
}

void CallibriSignalModel::setSinePhase(int phase){
    auto sineGenerator = sineGeneratorPtr.lock();
    if (!sineGenerator)
        return;

    sineGenerator->setPhase(phase);
    emit sinePhaseChanged();
}

void CallibriSignalModel::setNoiseAmplitude(int amplitude){
    noiseAmpl = amplitude;
    emit noiseAmplitudeChanged();
}

void CallibriSignalModel::setGainIndex(int gainIndex){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setGain(static_cast<Nes::Gain>(gainIndex));
    emit gainIndexChanged();
}

void CallibriSignalModel::setAdcInputIndex(int adcInputIndex){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setAdcInputState(static_cast<Nes::AdcInputState>(adcInputIndex));
    emit samplingFrequencyChanged();
}

void CallibriSignalModel::emitAll(){
    emit samplingFrequencyChanged();
    emit sineAmplitudeChanged();
    emit sineFrequencyChanged();
    emit sinePhaseChanged();
    emit noiseAmplitudeChanged();
    emit adcInputIndexChanged();
    emit gainIndexChanged();
}
