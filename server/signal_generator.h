#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#include "nes_types.h"

namespace Nes {

class SignalGenerator{
public:
    virtual ~SignalGenerator() = default;
    virtual std::vector<double> generateUv(std::size_t offset,
                                       std::size_t length,
                                       std::size_t sampling_freq) = 0;
};

}
#endif // SIGNAL_GENERATOR_H
