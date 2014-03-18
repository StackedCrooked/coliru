#include <iostream>
#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>

template <typename... Ts> struct referred_sizeof;

// base cases
template <typename T> struct referred_sizeof<T> { 
    static constexpr size_t value = sizeof(T);
};

template <typename T> struct referred_sizeof<T*> { 
    static constexpr size_t value = referred_sizeof<T>::value;
};

template <typename T> struct referred_sizeof<boost::optional<T*> > { 
    static constexpr size_t value = sizeof(boost::optional<T*>) + referred_sizeof<T>::value;
};

template <typename... Ts> struct referred_sizeof<boost::tuple<Ts...> > { 
    static constexpr size_t value = referred_sizeof<Ts...>::value; // TODO take into account padding/alignment overhead?
};

static_assert(referred_sizeof<int>::value == referred_sizeof<int*>::value, "passes");

template <typename T1, typename... Ts> struct referred_sizeof<T1, Ts...> {
    static constexpr size_t value = referred_sizeof<T1>::value + referred_sizeof<Ts...>::value;
};

template <typename T>
void report()
{
    std::cout << __PRETTY_FUNCTION__ << ": referred_sizeof is " << referred_sizeof<T>::value << "\n";
}

int main()
{
    report<double>();
    report<double *>();
    report<boost::optional<double> >();
    report<boost::optional<double> *>();
    report<boost::optional<double *> *>();

    report<boost::tuple<boost::optional<double *> *, double> >();
}
