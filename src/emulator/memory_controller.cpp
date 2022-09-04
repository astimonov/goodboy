#include "memory_controller.hpp"
#include "memory_interface.hpp"
#include "types.hpp"

using namespace Goodboy;

Byte MemoryController::Load(Address address)
{
    auto& mapping = GetMapping(address, AccessMode::Read);
    return mapping.memory.Load(address - mapping.startAddress);
}

void MemoryController::Store(Address address, Byte value)
{
    auto& mapping = GetMapping(address, AccessMode::Write);
    mapping.memory.Store(address - mapping.startAddress, value);
}

Mapping& MemoryController::GetMapping(Address address)
{
    for (auto& mapping : mMapping)
        if ((address >= mapping.startAddress) && (address <= mapping.endAddress))
            return mapping;
    return mFaultMapping;
}

Mapping& MemoryController::GetMapping(Address address, AccessMode accessMode)
{
    auto& mapping = GetMapping(address);
    if ((accessMode & mapping.accessMode) == accessMode)
        return mapping;
    return mFaultMapping;
}
