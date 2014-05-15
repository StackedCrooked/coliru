#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>

using namespace std;


struct Void{
    static constexpr int size = 0;
};

template<typename T0, typename T1>
class Variadic{
private:
    typedef Variadic<T0, T1> thisT;

public:
    /** Do not use this constructor */
    Variadic(T0 el0, T1 el1): value(el0), next(el1) {}

    // avoiding decltype
    typedef T0 valueT;
    T0 value;

    typedef T1 nextT;
    T1 next; // may be next pair

    /**
     * Chainable method
     */
    template<typename ValueT>
    /*constexpr*/ inline Variadic<ValueT, thisT> add(ValueT value){
        return Variadic<ValueT, thisT>(value, (*this) );
    }

};

template<typename T>
/*constexpr*/ static inline Variadic<T, Void> make_variadic(T value){
    return Variadic<T, Void>(value, Void());
}



template<typename Arg0, typename... Args>
static inline auto make_variadic(Arg0 value0, Args... values) -> decltype( fill(make_variadic<Arg0>(value0), values...) ) {
    return fill(make_variadic<Arg0>(value0), values...);
}

/*
template<typename Arg0, typename... Args>
static inline auto make_variadic(Arg0 value0, Args... values) -> decltype(fill(Variadic<Arg0, Void>(value0, Void()), values...)) {
    return fill(Variadic<Arg0, Void>(value0, Void()), values...);
}*/


template<typename T, typename Arg0, typename... Args>
static inline auto fill(T self, Arg0 value, Args... values) -> decltype(fill(self.add(value), values...)){
    return fill(self.add(value), values...);
}

template<typename T, typename Arg0>
static inline auto fill(T self, Arg0 value) -> decltype(self.add(value)){
    return self.add(value);
}



int main()
{
    auto list = make_variadic(1, 2, 3);
}
