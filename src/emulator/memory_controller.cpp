#include "memory_controller.hpp"
#include "memory_interface.hpp"
#include "types.hpp"

using namespace Goodboy;

Byte MemoryController::Load(Address address)
{
    return GetMemory(address, AccessMode::Read).Load(address);
}

void MemoryController::Store(Address address, Byte value)
{
    GetMemory(address, AccessMode::Write).Store(address, value);
}

Mapping& MemoryController::GetMapping(Address address)
{
    for (auto& mapping : mMapping)
        if ((address >= std::get<0>(mapping)) && (address <= std::get<1>(mapping)))
            return mapping;
    return mFaultMapping;
}

MemoryInterface& MemoryController::GetMemory(Address address, AccessMode accessMode)
{
    auto mapping = GetMapping(address);
    if ((accessMode & std::get<2>(mapping)) == accessMode)
        return std::get<3>(mapping);
    return std::get<3>(mFaultMapping);
}
