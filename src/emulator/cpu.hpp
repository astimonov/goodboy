#ifndef EMULATOR_CPU_HPP
#define EMULATOR_CPU_HPP

#include "memory_controller.hpp"
#include "memory_interface.hpp"
#include "types.hpp"

namespace Goodboy
{
    class Cpu
    {
    private:
        MemoryController mMemoryController = MemoryController();
    };
}

#endif // EMULATOR_CPU_HPP
