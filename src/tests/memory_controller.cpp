#include "memory_controller.hpp"
#include "types.hpp"

#include <gtest/gtest.h>

namespace Goodboy
{
    class MemoryControllerTestWrapper : public MemoryController
    {
    public:
        using MemoryController::NotUsableStart;
        using MemoryController::NotUsableEnd;
        using MemoryController::Wram0Start;
        using MemoryController::Wram1End;
        using MemoryController::RomBank00Start;
        using MemoryController::RomBank00End;
    };
}

using namespace Goodboy;

TEST(MemoryControllerTest, ResetState)
{
    MemoryControllerTestWrapper memoryController;
    const MemoryControllerTestWrapper& memoryControllerConst { memoryController };

    for (size_t address = memoryController.RomBank00Start; address < memoryController.NotUsableStart; address++)
        EXPECT_EQ(memoryController.Load(static_cast<Address>(address)), 0x00);

    for (size_t address = memoryController.NotUsableStart; address <=memoryController. NotUsableEnd; address++)
        EXPECT_EQ(memoryController.Load(static_cast<Address>(address)), 0xA5);

    for (size_t address = memoryController.NotUsableEnd + 1; address <= 0xFF; address++)
        EXPECT_EQ(memoryController.Load(static_cast<Address>(address)), 0x00);
}

TEST(MemoryControllerTest, BasicStoreLoad)
{
    constexpr Byte checkValue { 0x5A };
    MemoryControllerTestWrapper memoryController;

    memoryController.Store(memoryController.Wram0Start, checkValue);
    EXPECT_EQ(memoryController.Load(memoryController.Wram0Start), checkValue);
}

TEST(MemoryControllerTest, Fill)
{
    Byte checkValue { 0x00 };
    MemoryControllerTestWrapper memoryController;

    for (size_t address = memoryController.Wram0Start; address <= memoryController.Wram1End; address++)
    {
        memoryController.Store(static_cast<Address>(address), checkValue);
        EXPECT_EQ(memoryController.Load(static_cast<Address>(address)), checkValue);
        checkValue++;
    }
}

TEST(MemoryControllerTest, ReadOnly)
{
    MemoryControllerTestWrapper memoryController;

    for (size_t address = memoryController.RomBank00Start; address <= memoryController.RomBank00End; address++)
    {
        memoryController.Store(static_cast<Address>(address), 0x5A);
        EXPECT_EQ(memoryController.Load(static_cast<Address>(address)), 0x00);
    }
}

TEST(MemoryControllerTest, SubscriptOperator)
{
    MemoryControllerTestWrapper memoryController;
    const MemoryControllerTestWrapper& memoryControllerConst { memoryController };
    constexpr Byte checkValue { 0x5A };
    constexpr Address addressReadOnly { memoryController.RomBank00Start };
    constexpr Address addressReadWrite { memoryController.Wram0Start };

    EXPECT_EQ(memoryControllerConst[addressReadOnly], 0x00);
    EXPECT_EQ(memoryControllerConst[addressReadWrite], 0x00);
    EXPECT_EQ(memoryController[addressReadWrite], 0x00);
    memoryController[addressReadWrite] = checkValue;
    EXPECT_EQ(memoryController[addressReadWrite], checkValue);
    EXPECT_EQ(memoryControllerConst[addressReadWrite], checkValue);
}
