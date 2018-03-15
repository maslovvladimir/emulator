#ifndef CALLIBRI_MODULE_CONTAINER_H
#define CALLIBRI_MODULE_CONTAINER_H

#include <memory>
#include <list>
#include "callibri_module.h"

namespace Nes
{

template <template <typename...> class T>
class CallibriModuleContainer{
public:
    using CallibriModulePtr = std::shared_ptr<CallibriModule>;
    using size_type = typename T<CallibriModulePtr>::size_type;
    using iterator = typename T<CallibriModulePtr>::iterator;
    using const_iterator = typename T<CallibriModulePtr>::const_iterator;
    using reference = typename T<CallibriModulePtr>::reference;
    using const_reference = typename T<CallibriModulePtr>::const_reference;

    CallibriModuleContainer(std::initializer_list<CallibriModulePtr> init_list);
    CallibriModuleContainer(const CallibriModuleContainer &) = delete;
    CallibriModuleContainer& operator=(const CallibriModuleContainer &) = delete;
    ~CallibriModuleContainer() = default;

    size_type size() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reference back();
    const_reference back() const;

    void add(CallibriModulePtr);

private:
    T<CallibriModulePtr> container;
};

using CallibriModuleList = CallibriModuleContainer<std::list>;

template <template <typename...> class T>
CallibriModuleContainer<T>::CallibriModuleContainer(std::initializer_list<CallibriModulePtr> init_list){
    for (auto& module : init_list){
        add(module);
    }
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::size() const -> size_type{
    return container.size();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::begin() -> iterator{
    return container.begin();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::begin() const -> const_iterator{
    return container.begin();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::cbegin() const -> const_iterator{
return container.cbegin();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::end() -> iterator{
    return container.end();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::end() const -> const_iterator{
    return container.end();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::cend() const -> const_iterator{
    return container.cend();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::back() -> reference{
    return container.back();
}

template <template <typename...> class T>
auto CallibriModuleContainer<T>::back() const -> const_reference{
    return container.back();
}


template <template <typename...> class T>
void CallibriModuleContainer<T>::add(CallibriModulePtr module){
    if (size() > 0){
        module->setSuccessor(back());
    }

    container.push_back(module);
}

}

#endif // CALLIBRI_MODULE_CONTAINER_H
