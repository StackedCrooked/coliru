#include <array>
#include <iostream>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>

template<typename T>
struct is_unsigned_integral
  : boost::mpl::and_<std::is_integral<T>, std::is_unsigned<T>>
{};

template<typename T, std::size_t From, std::size_t To>
struct bitmask : std::integral_constant<T, ((1 << To - From) - 1) << From>
{
    static_assert(is_unsigned_integral<T>::value, "Not a compatible type");
    static_assert(From < To, "Invalid range");
    static_assert(To < (sizeof(T) << 3), "Range too big");
};

template<typename T, typename... Fs>
T dynamic_at_c(std::size_t index)
{
    static_assert(boost::mpl::fold<boost::mpl::vector<Fs...>, boost::mpl::true_, boost::mpl::and_<std::is_convertible<boost::mpl::_2, T>, boost::mpl::_1>>::value, "");
    static const std::array<T, sizeof...(Fs)> table{Fs::value...};  
    return table[index];
}

struct reduce_op
{
    template<typename T1, typename T2>
    struct apply
    {
        using type = T1;
    };
};

template<typename S>
struct reduce
  : boost::mpl::fold<S, typename boost::mpl::front<S>::type, reduce_op>
{};

template<typename T, typename... Fs>
struct bitfield
{
public:


private:
    template<typename... Ts>
    auto at_c(std::size_t index) const 
        -> typename reduce<boost::mpl::vector<Ts...>>::type
    {
        return std::array<
            typename reduce<boost::mpl::vector<Ts...>>::type
          , sizeof...(Ts)
        >(Ts::value...)[index];        
    }
};

int main(int argc, char* argv[])
{
    std::cout << "Hi!" << std::endl;
    
    return 0;
}
