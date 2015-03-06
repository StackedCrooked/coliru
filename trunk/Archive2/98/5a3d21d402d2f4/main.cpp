#include <type_traits>
#include <iostream>

enum class Option
{
    PrintHi = 1 << 0,
    PrintYo = 1 << 1,
    PrintAlot = 1 << 2
};

template <typename T>
class EnumFlag
{
public:
    using UnderlayingType = typename std::underlying_type<T>::type;

    EnumFlag(const T& flags)
        : m_flags(static_cast<UnderlayingType>(flags))
    {}

    bool operator & (T r) const
    {
        return 0 != (m_flags & static_cast<UnderlayingType>(r));
    }

    static const T NoFlag = static_cast<T>(0);

private:
    UnderlayingType  m_flags;
};
template<typename T>
EnumFlag<typename std::enable_if<std::is_same<T, Option>::value, T>::type> operator | (T l, T r)
{
    return static_cast<T>(static_cast<typename EnumFlag<T>::UnderlayingType>(l) | static_cast<typename EnumFlag<T>::UnderlayingType>(r));
}

class ClassWithFlags
{
public:
    using Options = EnumFlag < Option >;

    void doIt(const Options &options);
};

void ClassWithFlags::doIt(const Options &options)
{
    if (options & Option::PrintHi)
    {
        std::cout << "Hi" << std::endl;
    }
    if (options & Option::PrintYo)
    {
        std::cout << "Yo!" << std::endl;
    }
}

int main()
{
    ClassWithFlags classWithFlags;
    classWithFlags.doIt(Option::PrintHi | Option::PrintAlot);
}