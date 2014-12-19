#include <iostream>
#include <map>
#include <algorithm> // for_each
#include <type_traits>

template <typename T>
struct is_pair
{
    // definicja ale nie deklaracja
    static constexpr bool value = false;
};

//delaracja
//template <typename T> constexpr bool is_pair<T>::value;

template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2> >
{
    static constexpr bool value = true;
};

//template <typename T1, typename T2> constexpr bool is_pair<std::pair<T1, T2>>::value;

template <typename T, bool B = true>
struct PairPrinter
{
    static_assert(is_pair<T>::value, "typename T is not a std::pair!");

    //immediate context

    template <bool C = B>
    void operator()(T const &e, typename std::enable_if<C, int>::type = 0)
    {
        std::cout << e.first;
    }

    template <bool C = B>
    void operator()(T const &e, typename std::enable_if<!C, int>::type = 0)
    {
        std::cout << e.second;
    }
};

int main()
{
    std::map<std::string, int> map;
    
    map.insert(
        std::make_pair(
            "Mieszko",
            966
        )
    );
    
    map.insert(
        std::make_pair(
            "Bolesław",
            1024
        )
    );
    
    PairPrinter<std::pair<std::string, int> > firstPrinter;
    PairPrinter<std::pair<std::string, int>, false > secondPrinter;
    
    std::for_each(map.begin(), map.end(), firstPrinter);
    std::for_each(map.begin(), map.end(), secondPrinter);
    
}
