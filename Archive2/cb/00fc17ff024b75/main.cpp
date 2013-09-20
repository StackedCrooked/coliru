template <unsigned...> struct Sum;

template <unsigned size>
struct Sum<size>
{
    enum { value = size };
};

template <unsigned size, unsigned... sizes>
struct Sum<size, sizes...> 
{
    enum { value = size + Sum<sizes...>::value };
};

#include <cstdint>

template <unsigned bits> struct Store;
template <> struct Store<8> { typedef uint8_t Type; };
template <> struct Store<16> { typedef uint16_t Type; };
template <> struct Store<32> { typedef uint32_t Type; };
template <> struct Store<64> { typedef uint64_t Type; };

template <unsigned... sizes>
class Bitfields {
    typename Store<Sum<sizes...>::value>::Type store;
    public:
    constexpr Bitfields()
    {
    }
    
    template <unsigned pos, unsigned b4,
             unsigned size, unsigned... more>
                 friend unsigned getImpl(Bitfields<size, more...>);
};

template <unsigned pos, unsigned b4,
         unsigned size, unsigned... sizes>
         unsigned getImpl(Bitfields<size, sizes...> bf) 
         {
             static_assert(pos <= sizeof...(sizes), "Invalid bitfield access");
             if (pos == 0) 
             {
                 if (size == 1)
                 {
                     return (bf.store & (1u << b4)) != 0;
                 }
                 return (bf.store >> b4) & ((1u << size) - 1);
             }
             else
             {
                return getImpl<pos - (pos ? 1 : 0), b4 + (pos ? size : 0)>(bf);
             }
         }

template <unsigned pos, unsigned... sizes>
unsigned get(Bitfields<sizes...> bf)
{
    return getImpl<pos, 0>(bf);
}

#include <iostream>

enum Bits : unsigned
{
    Present = 0,
    ReadWrite,
    UserMode,
    WriteThrough,
    CacheDisabled,
    Accessed,
    Dirty,
    Zero,
    Global,
    AVAIL,
    Frame
};

#include <array>

std::array<Bits, 12> bits_array{{Bits::Present,
                                 Bits::ReadWrite,
                                 Bits::UserMode,
                                 Bits::WriteThrough,
                                 Bits::CacheDisabled,
                                 Bits::Accessed,
                                 Bits::Dirty,
                                 Bits::Zero,
                                 Bits::Global,
                                 Bits::AVAIL,
                                 Bits::Frame}};

constexpr unsigned bits_calc(unsigned b)
{
    return b == Bits::Present       ? 1 :
           b == Bits::ReadWrite     ? 1 :
           b == Bits::UserMode      ? 1 :
           b == Bits::WriteThrough  ? 1 :
           b == Bits::CacheDisabled ? 1 :
           b == Bits::Accessed      ? 1 :
           b == Bits::Dirty         ? 1 :
           b == Bits::Zero          ? 1 :
           b == Bits::Global        ? 1 :
           b == Bits::AVAIL         ? 3 :
           b == Bits::Frame         ? 20 :
           0;
}

// Function pointer template, to ease implementing apply_phase
template<typename ReturnType, typename... Parameters>
using FunctionPointer = ReturnType (*)(Parameters...);

template<int...>
struct Sequence
{
};

template<int N, int... S>
struct GenerateSequence : GenerateSequence<N-1, N-1, S...>
{
};

template<int... S>
struct GenerateSequence<0, S...> 
{
  typedef Sequence<S...> type;
};

#include <array>

template<typename OUTPUT, typename INPUT, unsigned long SIZE>
constexpr std::array<OUTPUT, SIZE> convert(std::array<INPUT, SIZE> input)
{
    return convert<OUTPUT>(input, typename GenerateSequence<SIZE>::type());
}

template<typename OUTPUT, typename INPUT, unsigned long SIZE, int... S>
constexpr std::array<OUTPUT, SIZE> convert(std::array<INPUT, SIZE> input, const Sequence<S...>)
{
    return std::array<OUTPUT, SIZE>{{std::get<S>(input)...}};
}

template<typename ENUM, unsigned long SIZE>
constexpr auto make_bitfield(const std::array<ENUM, SIZE> enums, const FunctionPointer<unsigned, unsigned> func)
    -> decltype(make_bitfield_worker(convert<unsigned>(enums), func, typename GenerateSequence<SIZE>::type()))
{
    return make_bitfield_worker(convert<unsigned>(enums), func, typename GenerateSequence<SIZE>::type());
}

template<unsigned long SIZE, int... S>
constexpr auto make_bitfield_worker(const std::array<unsigned, SIZE> enums, const FunctionPointer<unsigned, unsigned> func, const Sequence<S...>)
    -> Bitfields<4,4,4,4> //Bitfields<func(std::get<S>(enums))...>
{
    return Bitfields<std::get<S>(enums)...>();
    //return Bitfields<func(std::get<S>(enums))...>();
}

int main()
{
    auto bf2 = make_bitfield(bits_array, bits_calc);

    Bitfields<4,4,4,4> bf; // 16 bits
//bf.setStore(0); // clear entire bitfield
    // set<1>(bf, 6);
    // sets second field to 6
    auto x = get<2>(bf); // gets third field
    
    std::cout << x << std::endl;
}
