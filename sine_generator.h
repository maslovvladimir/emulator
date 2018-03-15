#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#include "server/signal_generator.h"

class SineGenerator final : public Nes::SignalGenerator{
public:
    std::vector<double> generateUv(std::size_t offsetUv,
                             std::size_t length,
                             std::size_t sampling_freq) override;
    void setAmplitudeUV(int);
    void setFrequency(int);
    void setPhase(int);
    void setOffsetUv(int);

    int getAmplitudeUV() const;
    int getFrequency() const;
    int getPhase() const;
    int getOffsetUv() const;

private:
    int amplitudeUV{50};
    int frequency{5};
    int phase{0};
    int offsetUv{0};
};

#endif // SINE_GENERATOR_H
