#ifndef EMULATOR_MEMORY_CONTROLLER_HPP
#define EMULATOR_MEMORY_CONTROLLER_HPP

#include "memory_interface.hpp"
#include "random_access_memory.hpp"
#include "stub_memory.hpp"

#include <map>
#include <type_traits>

namespace Goodboy
{
    enum class AccessMode : uint8_t
    {
        None = 0,
        Read = 1,
        Write = 2,
        ReadWrite = AccessMode::Read | AccessMode::Write,
    };

    constexpr AccessMode operator|(AccessMode a, AccessMode b)
    {
        using AccessModeType = std::underlying_type_t<AccessMode>;
        return static_cast<AccessMode>(static_cast<AccessModeType>(a) |
                                       static_cast<AccessModeType>(b));
    }

    constexpr AccessMode operator&(AccessMode a, AccessMode b)
    {
        using AccessModeType = std::underlying_type_t<AccessMode>;
        return static_cast<AccessMode>(static_cast<AccessModeType>(a) &
                                       static_cast<AccessModeType>(b));
    }

    struct Mapping
    {
        Address startAddress;
        Address endAddress;
        AccessMode accessMode;
        MemoryInterface& memory;
    };

    class MemoryController : public MemoryInterface
    {
    public:
        MemoryController() = default;

        ~MemoryController() = default;

        Byte Load(Address address) override;

        void Store(Address address, Byte value) override;

        Byte& operator[](Address address) override;

        const Byte operator[](Address address) const override;

    private:
        static constexpr std::size_t GetMappingSize(Address start, Address end)
        {
            return static_cast<std::size_t>(end)
                 - static_cast<std::size_t>(start)
                 + std::size_t(1);
        }

        static constexpr Address RomBank00Start     { 0x0000 };
        static constexpr Address RomBank01Start     { 0x4000 };
        static constexpr Address VideoRamStart      { 0x8000 };
        static constexpr Address ExternalRamStart   { 0xA000 };
        static constexpr Address Wram0Start         { 0xC000 };
        static constexpr Address Wram1Start         { 0xD000 };
        static constexpr Address EchoRam0Start      { 0xE000 };
        static constexpr Address EchoRam1Start      { 0xF000 };
        static constexpr Address OamStart           { 0xFE00 };
        static constexpr Address NotUsableStart     { 0xFEA0 };
        static constexpr Address IoStart            { 0xFF00 };
        static constexpr Address HramStart          { 0xFF80 };
        static constexpr Address IeStart            { 0xFFFF };

        static constexpr Address RomBank00End       { 0x3FFF };
        static constexpr Address RomBank01End       { 0x7FFF };
        static constexpr Address VideoRamEnd        { 0x9FFF };
        static constexpr Address ExternalRamEnd     { 0xBFFF };
        static constexpr Address Wram0End           { 0xCFFF };
        static constexpr Address Wram1End           { 0xDFFF };
        static constexpr Address EchoRam0End        { 0xEFFF };
        static constexpr Address EchoRam1End        { 0xFDFF };
        static constexpr Address OamEnd             { 0xFE9F };
        static constexpr Address NotUsableEnd       { 0xFEFF };
        static constexpr Address IoEnd              { 0xFF7F };
        static constexpr Address HramEnd            { 0xFFFE };
        static constexpr Address IeEnd              { 0xFFFF };

        RandomAccessMemory mRomBank00   { GetMappingSize(RomBank00Start,     RomBank00End) };
        RandomAccessMemory mRomBank01   { GetMappingSize(RomBank01Start,     RomBank01End) };
        RandomAccessMemory mVideoRam    { GetMappingSize(VideoRamStart,      VideoRamEnd) };
        RandomAccessMemory mExternalRam { GetMappingSize(ExternalRamStart,   ExternalRamEnd) };
        RandomAccessMemory mWram0       { GetMappingSize(Wram0Start,         Wram0End) };
        RandomAccessMemory mWram1       { GetMappingSize(Wram1Start,         Wram1End) };
        RandomAccessMemory mOam         { GetMappingSize(OamStart,           OamEnd) };
        RandomAccessMemory mIo          { GetMappingSize(IoStart,            IoEnd) };
        RandomAccessMemory mHram        { GetMappingSize(HramStart,          HramEnd) };
        RandomAccessMemory mIe          { GetMappingSize(IeStart,            IeEnd) };
        StubMemory         mStubMemory;

        std::vector<Mapping> mMapping
        {
            {RomBank00Start,    RomBank00End,   AccessMode::Read,       mRomBank00},
            {RomBank01Start,    RomBank01End,   AccessMode::Read,       mRomBank01},
            {VideoRamStart,     VideoRamEnd,    AccessMode::ReadWrite,  mVideoRam},
            {ExternalRamStart,  ExternalRamEnd, AccessMode::ReadWrite,  mExternalRam},
            {Wram0Start,        Wram0End,       AccessMode::ReadWrite,  mWram0},
            {Wram1Start,        Wram1End,       AccessMode::ReadWrite,  mWram1},
            {EchoRam0Start,     EchoRam0End,    AccessMode::Read,       mWram0},
            {EchoRam1Start,     EchoRam1End,    AccessMode::Read,       mWram1},
            {OamStart,          OamEnd,         AccessMode::ReadWrite,  mOam},
            {NotUsableStart,    NotUsableEnd,   AccessMode::None,       mStubMemory},
            {IoStart,           IoEnd,          AccessMode::ReadWrite,  mIo},
            {HramStart,         HramEnd,        AccessMode::ReadWrite,  mHram},
            {IeStart,           IeEnd,          AccessMode::ReadWrite,  mIe}
        };

        Mapping mFaultMapping { 0, 0, AccessMode::None, mStubMemory };

        Mapping& GetMapping(Address address);
        const Mapping& GetMapping(Address address) const;
        Mapping& GetMapping(Address address, AccessMode accessMode);
        const Mapping& GetMapping(Address address, AccessMode accessMode) const;

        friend class MemoryControllerTestWrapper;
    };
}

#endif // EMULATOR_MEMORY_CONTROLLER_HPP
