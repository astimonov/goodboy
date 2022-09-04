#ifndef EMULATOR_RANDOM_ACCESS_MEMORY_HPP
#define EMULATOR_RANDOM_ACCESS_MEMORY_HPP

#include "memory_interface.hpp"

#include <vector>

namespace Goodboy
{
    class RandomAccessMemory : public MemoryInterface
    {
    public:
        RandomAccessMemory(std::size_t size)
            : mMemory(size)
        {

        }

        ~RandomAccessMemory() = default;

        Byte Load(Address address) override
        {
            return mMemory[address];
        }

        void Store(Address address, Byte value) override
        {
            mMemory[address] = value;
        }

    private:
        std::vector<Byte> mMemory;
    };
}

#endif // EMULATOR_RANDOM_ACCESS_MEMORY_HPP
