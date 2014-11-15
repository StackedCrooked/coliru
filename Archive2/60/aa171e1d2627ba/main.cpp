#include <type_traits>
#include <cstdint>

template <class...> struct null_v : std::integral_constant<int, 0> {};

template <bool B, typename T = void> using enable_if_t = typename std::enable_if<B, T>::type;
template <bool B, typename T = void> using disable_if_t = typename std::enable_if<!B, T>::type;

template <std::intmax_t A> struct SStruct
{
    static constexpr std::intmax_t a = A;
};

template <typename T> struct SCheckEnable : std::integral_constant<bool, T::a == 0>
{
};

template <typename U, typename T> class CClass
{
    public:
        template <typename T2, long = null_v<enable_if_t<SCheckEnable<U>::value, T2>>::value> constexpr CClass(T2 v) : val(v) {};
        template <typename T2, int = null_v<disable_if_t<SCheckEnable<U>::value, T2>>::value> explicit constexpr CClass(T2 v) : val(v) {};

    private:
        T val;
};

int main()
{
    CClass<SStruct<0>, double> a = 1;                             // should use implicit constructor
    CClass<SStruct<1>, double> b = CClass<SStruct<1>, double>(1); // should use explicit constructor
}
