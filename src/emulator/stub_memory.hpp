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
            return mValue;
        }

        void Store(Address address, Byte value) override
        {
            mValue = value;
        }

        Byte& operator[](Address address) override
        {
            return mValue;
        }

        const Byte operator[](Address address) const override
        {
            return mValue;
        }

    private:
        Byte mValue {0xA5};
    };
}

#endif // EMULATOR_STUB_MEMORY_HPP
