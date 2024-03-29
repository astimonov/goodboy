#ifndef EMULATOR_REGISTER_HPP
#define EMULATOR_REGISTER_HPP

#include "types.hpp"

#include <limits>

namespace Goodboy
{
    template<typename T>
    class Register
    {
    public:
        T& Value()
        {
            return mValue;
        }

        T& operator *()
        {
            return mValue;
        }

    private:
        T mValue {0};
    };

    template<typename T = Byte, typename D = Word>
    class RegisterPair
    {
    public:
        RegisterPair(Register<T>& high, Register<T>& low)
            : mHigh(high), mLow(low)
        {

        }

        T& Low()
        {
            return mLow.Value();
        }

        T& High()
        {
            return mHigh.Value();
        }

        D operator *() const
        {
            return (*mHigh << std::numeric_limits<T>::digits) | *mLow;
        }

        D Set(T high, T low)
        {
            *mHigh = high;
            *mLow = low;
            return **this;
        }
    private:
        Register<T>& mHigh;
        Register<T>& mLow;
    };

    class FlagRegister
    {
    public:
        FlagRegister(RegisterPair<>& reg)
            : mRegister(reg)
        {

        }

        bool Z()
        {
            return GetFlag(mRegister.Low(), ZeroFlagBit);
        }

        bool Z(bool value)
        {
            return SetFlag(mRegister.Low(), ZeroFlagBit, value);
        }

        bool N()
        {
            return GetFlag(mRegister.Low(), SubstractionFlagBit);
        }

        bool N(bool value)
        {
            return SetFlag(mRegister.Low(), SubstractionFlagBit, value);
        }

        bool H()
        {
            return GetFlag(mRegister.Low(), HalfCarryFlagBit);
        }

        bool H(bool value)
        {
            return SetFlag(mRegister.Low(), HalfCarryFlagBit, value);
        }

        bool C()
        {
            return GetFlag(mRegister.Low(), CarryFlagBit);
        }

        bool C(bool value)
        {
            return SetFlag(mRegister.Low(), CarryFlagBit, value);
        }

    private:
        RegisterPair<>& mRegister;

        static constexpr auto ZeroFlagBit = 7;
        static constexpr auto SubstractionFlagBit = 6;
        static constexpr auto HalfCarryFlagBit = 5;
        static constexpr auto CarryFlagBit = 4;

        bool GetFlag(Byte& byte, std::size_t bit)
        {
            return byte & (Byte(1) << bit);
        }

        bool SetFlag(Byte& byte, std::size_t bit, bool value)
        {
            auto mask = (Byte(1) << bit);

            if (value)
                byte |= mask;
            else
                byte &= ~mask;

            return value;
        }

        friend class FlagRegisterTestWrapper;
    };
}

#endif // EMULATOR_REGISTER_HPP
