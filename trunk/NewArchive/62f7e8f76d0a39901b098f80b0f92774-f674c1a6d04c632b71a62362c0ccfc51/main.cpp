struct X86 {};
struct X64 {};
struct ARM {};
struct PDP10 {};
struct PDP11 {};

#define _X86

#ifdef _X86
typedef X86 SystemArchitecture;
#endif
#ifdef _X64
typedef X64 SystemArchitecture
#endif
#ifdef _ARM
typedef ARM SystemArchitecture;
#endif
#ifdef _PDP10
typedef PDP10 SystemArchitecture
#endif
#ifdef _PDP11
typedef PDP11 SystemArchitecture
#endif

#include <iostream>
#include <typeinfo>

enum Endianness_Types
{
    little_endian,
    middle_endian,
    big_endian,
    bi_endian
};

template<typename T>
struct Endianness {};

template<>
struct Endianness<X86>
{
    static constexpr Endianness_Types type = little_endian;
};

template<>
struct Endianness<X64>
{
    static constexpr Endianness_Types type = little_endian;
};

template<>
struct Endianness<ARM>
{
    static constexpr Endianness_Types type = bi_endian;
};

template<>
struct Endianness<PDP10>
{
    static constexpr Endianness_Types type = big_endian;
};

template<>
struct Endianness<PDP11>
{
    static constexpr Endianness_Types type = middle_endian;
};

template<typename T>
struct GeneralPurposeRegisters {};

template<>
struct GeneralPurposeRegisters<X86>
{
    uint32_t EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI;
};



int main()
{
    Endianness_Types system_type = Endianness<SystemArchitecture>::type;
    std::cout << typeid(SystemArchitecture).name() << std::endl;
}