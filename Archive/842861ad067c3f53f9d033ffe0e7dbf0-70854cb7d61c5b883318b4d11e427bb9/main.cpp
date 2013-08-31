template<typename T, typename U>
struct is_same { static constexpr bool value = false; };

template<typename T>
struct is_same<T, T> { static constexpr bool value = true; };

template<bool C, typename T = void>
struct enable_if { };

template<typename T>
struct enable_if<true, T> { using type = T; };

template<class... Args> struct SimpleTuple;

template<> struct SimpleTuple<> {
    SimpleTuple() { }
};

template<class Head, class... Tail>
struct SimpleTuple<Head, Tail...> {
    typedef Head    HeadType;
    typedef SimpleTuple<Tail...> VATailType;

    SimpleTuple(Head head, Tail... tail) : data(head), rest(tail...) { }

    template<typename T, 
        typename enable_if<!is_same<T, Head>::value>::type* = nullptr>
    T& get() {
        return rest.get<T>();
    }

    template<typename T, 
        typename enable_if<is_same<T, Head>::value>::type* = nullptr>
    Head& get() {
        return data;
    }

    Head data;
    VATailType rest;
};

#include <iostream>

int main()
{
    SimpleTuple<int, double, char> t{1, 2.0, 'c'};
    std::cout << t.get<double>();
}
