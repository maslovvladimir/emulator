#ifndef CALLIBRI_GENERIC_MODULE_H
#define CALLIBRI_GENERIC_MODULE_H

#include <algorithm>
#include <array>
#include <functional>
#include <map>
#include "callibri_module.h"
#include "callibri_command.h"
#include "callibri_common_parameters.h"

namespace Nes
{

template <CallibriCommandCode... Commands>
class CallibriGenericModule : public CallibriModule{
public:
    CallibriGenericModule(std::shared_ptr<CallibriCommonParameters>) noexcept;
protected:
    std::shared_ptr<CallibriCommonParameters> commonParameters;
private:
    std::array<CallibriCommandCode, sizeof...(Commands)> supportedCommands{{Commands...}};
    bool checkIfResponsible(const CallibriCommand &) noexcept override;
};

template <CallibriCommandCode... Commands>
CallibriGenericModule<Commands...>::CallibriGenericModule(std::shared_ptr<CallibriCommonParameters> common_params) noexcept :
    commonParameters(common_params){}

template <CallibriCommandCode... Commands>
bool CallibriGenericModule<Commands...>::checkIfResponsible(const CallibriCommand &command) noexcept {
    return std::find(supportedCommands.begin(), supportedCommands.end(), command.code()) != supportedCommands.end();
}

}

#endif // CALLIBRI_GENERIC_MODULE_H
