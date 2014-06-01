#include <iostream>
#include <type_traits>

// utility classes, don't consider
template <class T, T... I> struct integer_sequence
{
    template <T N> using append = integer_sequence<T, I..., N>;
    static std::size_t size () { return sizeof...(I); }
    using next = append<sizeof...(I)>;
    using type = T;
};
 
template <class T, T Index, std::size_t N>
struct sequence_generator 
{
    using type = typename sequence_generator<T, Index - 1, N - 1>::type::next;
};
 
template <class T, T Index>
struct sequence_generator<T, Index, 0ul> { using type = integer_sequence<T>; };
 
template <std::size_t... I>
using index_sequence = integer_sequence<std::size_t, I...>;
 
template <class T, T N>
using make_integer_sequence = typename sequence_generator<T, N, N>::type;
 
template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

template<typename... T>
struct remove_first_index_impl
{
    using type = index_sequence<>;
};

template<std::size_t First, std::size_t... I>
struct remove_first_index_impl<index_sequence<First, I...>>
{
    using type = index_sequence<I...>;
};

template<typename T>
using remove_first_index = typename remove_first_index_impl<T>::type;


using namespace std;

// here is the interesting part:

std::size_t multiply()
{
  return 1;
}

template<typename... T>
std::size_t multiply(std::size_t number, T... args)
{
  return number * multiply(args...);
}

template<typename T, typename B, typename C>
struct set_array_value;

template<typename T, size_t... DimCount>
struct set_array_value<T, std::true_type, index_sequence<DimCount...>>
{
    static std::size_t get_adress()
    {
        return 0;
    }
     template<typename... TArgs>
    static std::size_t get_adress(std::size_t index1, TArgs... args)
    {
        return  index1 * multiply(std::extent<T,DimCount>::value...) +
                         set_array_value<T, std::true_type, remove_first_index<index_sequence<DimCount...>>>::get_adress(args...);
    }

        template<typename... TArgs>
    static void set_value(T& arg, typename std::remove_all_extents<T>::type value, TArgs... args)
    {
        const auto adress =  set_array_value<T, std::true_type, remove_first_index<index_sequence<DimCount...>>>::get_adress(args...);
        *(reinterpret_cast<typename std::remove_all_extents<T>::type*>(arg) + adress) = value;
    }
};

template<typename T, size_t... DimCount>
struct set_array_value<T, std::false_type, index_sequence<DimCount...>>
{
    template<typename... TArgs>
    static void set_value(T& arg, TArgs... args)
    {
    }
};


template<typename T, typename... Indices>
void set_value(T& array,typename std::remove_all_extents<T>::type value, Indices... args)
{
   set_array_value<T, typename std::integral_constant<bool, std::rank<T>::value == sizeof...(args)>::type, make_index_sequence<sizeof...(args)>>::set_value(array, value, args...);
}


int main() {
	int foo[2][10] = {{0, 1,2,3,4,5,6,7,8,9}, {0, 1,2,3,4,5,6,7,8,9}};
    set_value(foo, 42, 3, 4);
    std::cout << foo[3][4] << std::endl;

	return 0;
}