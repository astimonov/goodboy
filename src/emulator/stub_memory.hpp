#ifndef EMULATOR_STUB_MEMORY_HPP
#define EMULATOR_STUB_MEMORY_HPP

#include "memory_interface.hpp"

namespace Goodboy
{
    class StubMemory : public MemoryInterface
    {
    public:
        StubMemory() = default;

        ~StubMemory() = default;

        Byte Load(Address address) override
        {
            return 0xA5;
        }

        void Store(Address address, Byte value) override
        {

        }
    };
}

#endif // EMULATOR_STUB_MEMORY_HPP
