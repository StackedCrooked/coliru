#include <iostream>
#include <vector>

using namespace std;

template<class T>struct tag{using type=T;};
template<class T>using block_deduction=typename tag<T>::type;

template<class...>struct types{using type=types;};

template<class lhs, class rhs>struct cat;
template<class lhs, class rhs>using cat_t=typename cat<lhs,rhs>::type;

template<class...lhs, class...rhs>
struct cat<types<lhs...>,types<rhs...>>:
  types<lhs...,rhs...>
{};

template<class types, size_t n>
struct split {
private:
  using s0 = split<types,n/2>;
  using r0 = typename s0::lhs;
  using r1 = typename s0::rhs;
  using s1 = split<r1,n-n/2>;
  using r2 = typename s1::lhs;
public:
  using lhs = cat_t<r0,r2>;
  using rhs = typename s1::rhs;
};
template<class Types>
struct split<Types, 0>{
  using lhs=types<>;
  using rhs=Types;
};
template<class T0,class...Ts>
struct split<types<T0,Ts...>,1>{
  using lhs=types<T0>;
  using rhs=types<Ts...>;
};
template<class types>
struct foo2_t;
template<class... T0s>
struct foo2_t<types<T0s...>>{
    template<class... T1s>
    void operator()(const T0s&&... t0s, T1s&&... t1s){
      std::cout << sizeof...(T0s) << '\n';
      std::cout << sizeof...(T1s) << '\n';
      
    typedef typename common_type<T0s...>::type T0;
    typedef typename common_type<T1s...>::type T1;

    std::vector<T0> x_array = { t0s... };

    for (auto it = x_array.begin(); it != x_array.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::vector<T1> y_array = { t1s... };

    for (auto it = y_array.begin(); it != y_array.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    auto tie_t0s = std::tie( std::forward<T0s>(t0s)... );
    (void)(tie_t0s);
    auto tie_t1s = std::tie( std::forward<T1s>(t1s)... );
    
    std::get<0>(tie_t1s) = 3.33;
//    y_array[0] = 3.33;  // does not affect the variable "c" within the main
                        // since y_array is a copy of t1s and not a reference
    }
};

template <class... Ts>
void foo(Ts&&... ts) {
  using s = split< types<Ts...>, sizeof...(Ts)/2 >;
  foo2_t<typename s::lhs>{}( std::forward<Ts>(ts)... );
}


int main()
{
    int a = 1;
    int b = 2;
    float c = 4.5;
    float d = 5.5;
    cout << "before:" << endl;
    cout << "a: " << a << endl << "b: " << b << endl << "c: " << c << endl << "d: " << d << endl << endl;
    foo(a, b, c, d);
    
    cout << endl;
    cout << "after:" << endl;
    cout << "a: " << a << endl << "b: " << b << endl << "c: " << c << endl << "d: " << d << endl << endl;

    return 0;
}