#include "sine_generator.h"
#include <cmath>

std::vector<double> SineGenerator::generateUv(std::size_t offset,
                                        std::size_t length,
                                        std::size_t sampling_freq){
    std::vector<double> samples(length);
    static const double two_pi = std::acos(-1)*2;
    if (sampling_freq < frequency)
        return samples;

    auto samplesPerPeriod = static_cast<double>(sampling_freq)/frequency;
    auto offsetShift = ((offset / samplesPerPeriod) - std::trunc(offset / samplesPerPeriod)) * 360.0;

    for (std::size_t i = 0; i<samples.size(); ++i){
        auto sampleTime = static_cast<double>(i) / sampling_freq;
        samples[i] = amplitudeUV*std::sin(frequency*two_pi*sampleTime + phase + offsetShift) + offsetUv;
    }
    return samples;
}

void SineGenerator::setAmplitudeUV(int ampl){
    amplitudeUV = ampl;
}

void SineGenerator::setFrequency(int freq){
    frequency = freq;
}

void SineGenerator::setPhase(int ph){
    phase = ph;
}

void SineGenerator::setOffsetUv(int of){
    offsetUv = of;
}

int SineGenerator::getAmplitudeUV() const {
    return amplitudeUV;
}

int SineGenerator::getFrequency() const {
    return frequency;
}

int SineGenerator::getPhase() const {
    return phase;
}

int SineGenerator::getOffsetUv() const {
    return offsetUv;
}
