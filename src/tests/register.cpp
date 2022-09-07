#include "register.hpp"

#include <gtest/gtest.h>

using namespace Goodboy;

template <typename T>
class RegisterTest : public testing::Test
{
public:
    using RegisterType = T;
};

using RegisterTypes = testing::Types<Byte, Word>;
TYPED_TEST_SUITE(RegisterTest, RegisterTypes);

TYPED_TEST(RegisterTest, TypedRegister)
{
    using RegisterType = typename TestFixture::RegisterType;
    Register<RegisterType> reg;
    constexpr RegisterType checkValue { static_cast<RegisterType>(0x5A5A5A5A5A5A5A5A) };

    EXPECT_EQ(*reg, 0);
    EXPECT_EQ(*reg = checkValue, checkValue);
    EXPECT_EQ(*reg, checkValue);
    EXPECT_EQ(reg.Value(), checkValue);
}

TEST(RegisterTest, RegisterPair)
{
    constexpr Byte High1 = 0x12;
    constexpr Byte Low1 = 0x34;
    constexpr Word HighLow1 = 0x1234;

    Register<Byte> high, low;
    RegisterPair<> pair(high, low);

    EXPECT_EQ(*pair, 0);
    EXPECT_EQ(pair.Set(High1, Low1), HighLow1);
    EXPECT_EQ(*pair, HighLow1);
    EXPECT_EQ(*high, High1);
    EXPECT_EQ(*low, Low1);

    constexpr Byte High2 = 0xAB;
    constexpr Byte Low2 = 0xCD;
    constexpr Word HighLow2 = 0xABCD;

    EXPECT_EQ(*high = High2, High2);
    EXPECT_EQ(*low = Low2, Low2);
    EXPECT_EQ(*pair, HighLow2);
}

namespace Goodboy
{
    class FlagRegisterTestWrapper : public FlagRegister
    {
    public:
        using FlagRegister::FlagRegister;

        using FlagRegister::ZeroFlagBit;
        using FlagRegister::SubstractionFlagBit;
        using FlagRegister::HalfCarryFlagBit;
        using FlagRegister::CarryFlagBit;
    };
}

TEST(RegisterTest, FlagRegister)
{
    Register<Byte> high, low;
    RegisterPair<> pair(high, low);
    FlagRegisterTestWrapper flags(pair);

    Word value = 0;
    EXPECT_EQ(*pair, value);
    EXPECT_FALSE(flags.Z());
    EXPECT_FALSE(flags.N());
    EXPECT_FALSE(flags.H());
    EXPECT_FALSE(flags.C());

    value |= (Byte(1) << flags.ZeroFlagBit);
    EXPECT_TRUE(flags.Z(true));
    EXPECT_TRUE(flags.Z());
    EXPECT_EQ(*pair, value);

    value |= (Byte(1) << flags.SubstractionFlagBit);
    EXPECT_TRUE(flags.N(true));
    EXPECT_TRUE(flags.N());
    EXPECT_EQ(*pair, value);

    value |= (Byte(1) << flags.HalfCarryFlagBit);
    EXPECT_TRUE(flags.H(true));
    EXPECT_TRUE(flags.H());
    EXPECT_EQ(*pair, value);

    value |= (Byte(1) << flags.CarryFlagBit);
    EXPECT_TRUE(flags.C(true));
    EXPECT_TRUE(flags.C());
    EXPECT_EQ(*pair, value);

    value &= ~(Byte(1) << flags.ZeroFlagBit);
    EXPECT_FALSE(flags.Z(false));
    EXPECT_FALSE(flags.Z());
    EXPECT_EQ(*pair, value);

    value &= ~(Byte(1) << flags.SubstractionFlagBit);
    EXPECT_FALSE(flags.N(false));
    EXPECT_FALSE(flags.N());
    EXPECT_EQ(*pair, value);

    value &= ~(Byte(1) << flags.HalfCarryFlagBit);
    EXPECT_FALSE(flags.H(false));
    EXPECT_FALSE(flags.H());
    EXPECT_EQ(*pair, value);

    value &= ~(Byte(1) << flags.CarryFlagBit);
    EXPECT_FALSE(flags.C(false));
    EXPECT_FALSE(flags.C());
    EXPECT_EQ(*pair, value);

    value |= (Byte(1) << flags.ZeroFlagBit);
    value |= (Byte(1) << flags.HalfCarryFlagBit);
    pair.Low() = value;
    EXPECT_TRUE(flags.Z());
    EXPECT_FALSE(flags.N());
    EXPECT_TRUE(flags.H());
    EXPECT_FALSE(flags.C());
}
