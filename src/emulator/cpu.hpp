#ifndef EMULATOR_CPU_HPP
#define EMULATOR_CPU_HPP

#include "memory_controller.hpp"
#include "memory_interface.hpp"
#include "register.hpp"
#include "types.hpp"

namespace Goodboy
{
    class Cpu
    {
    public:
        Cpu()
            : AF(A, F),
              BC(B, C),
              DE(D, E),
              HL(H, L),
              Flags(AF)
        {

        }

    private:
        MemoryController mMemoryController;
        Register<Byte> A, F,
                       B, C,
                       D, E,
                       H, L;
        RegisterPair<> AF,
                       BC,
                       DE,
                       HL;
        FlagRegister   Flags;
        Register<Word> SP, PC;
    };
}

#endif // EMULATOR_CPU_HPP
