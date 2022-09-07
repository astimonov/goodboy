#ifndef EMULATOR_MEMORY_INTERFACE_HPP
#define EMULATOR_MEMORY_INTERFACE_HPP

#include "types.hpp"

namespace Goodboy
{
    class MemoryInterface
    {
    public:
        virtual ~MemoryInterface() = default;
        virtual Byte Load(Address address) = 0;
        virtual void Store(Address address, Byte value) = 0;
        virtual Byte& operator[](Address address) = 0;
        virtual const Byte operator[](Address address) const = 0;
    };
}

#endif // EMULATOR_MEMORY_INTERFACE_HPP
