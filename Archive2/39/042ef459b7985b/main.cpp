#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <deque>

template<class T>
using to_std_bool = std::integral_constant<bool, !!T::value>;
template<class Lhv, class Rhv>
using and_type = std::integral_constant<bool, Lhv::value && Rhv::value>;
template<class Lhv, class Rhv>
using or_type = std::integral_constant<bool, Lhv::value || Rhv::value>;

#define FWD(...) (std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__))

#define G_BINOP(SYM) ([](auto&& lhv, auto&& rhv) -> decltype(auto){ return FWD(lhv) SYM FWD(rhv); })
#define G_PREFIXOP(SYM) ([](auto&& rhv) -> decltype(auto){ return SYM FWD(rhv); })
#define G_POSTFIXOP(SYM) ([](auto&& rhv) -> decltype(auto){ return FWD(rhv) SYM; })
#define G_FUNC(NAME) ([](auto&&... args) -> decltype(auto){ return NAME(FWD(args)...); })
#define G_METHOD(NAME) ([](auto&& obj, auto&&... args) -> decltype(auto){ return FWD(obj) . NAME (FWD(args)...); })
#define G_FIELD(NAME) ([](auto&& obj) -> decltype(auto){ return FWD(obj) . NAME; });

#define G_INDEXOP ([](auto&& lhv, auto&& arg) -> decltype(auto){ return FWD(lhv) [ FWD(arg) ]; })
#define G_CALLOP ([](auto&& lhv, auto&&... args) -> decltype(auto){ return FWD(lhv) ( FWD(args)... ); })

template<class T> T& declref();

#define GENERATE_COMPILES_TRAIT(NAME, VAR, ...) \
    template<class GENERATE_COMPILES_TRAIT_PARAM> \
    std::true_type NAME ## _f ( GENERATE_COMPILES_TRAIT_PARAM& VAR, decltype(__VA_ARGS__, 0)* = nullptr ); \
    std::false_type NAME ## _f (...); \
    template<class GENERATE_COMPILES_TRAIT_PARAM> using NAME = decltype(NAME ## _f(declref<GENERATE_COMPILES_TRAIT_PARAM>()));
    
#define GENERATE_COMPILES_BITRAIT(NAME, VAR0, VAR1, ...) \
    template<class GENERATE_COMPILES_TRAIT_PARAM0, class GENERATE_COMPILES_TRAIT_PARAM1> \
    std::true_type NAME ## _f ( GENERATE_COMPILES_TRAIT_PARAM0& VAR0, GENERATE_COMPILES_TRAIT_PARAM1& VAR1, decltype(__VA_ARGS__, 0)* = nullptr ); \
    std::false_type NAME ## _f (...); \
    template<class GENERATE_COMPILES_TRAIT_PARAM0, class GENERATE_COMPILES_TRAIT_PARAM1> using NAME = decltype(NAME ## _f(declref<GENERATE_COMPILES_TRAIT_PARAM0>(), declref<GENERATE_COMPILES_TRAIT_PARAM1>()));
   
    
GENERATE_COMPILES_TRAIT(is_equality_comparable, it, it == it)
GENERATE_COMPILES_TRAIT(is_less_than_comparable, it, it < it)

GENERATE_COMPILES_BITRAIT(is_std_swappable, lhv, rhv, std::swap(lhv, rhv))
GENERATE_COMPILES_BITRAIT(is_specially_swappable, lhv, rhv, swap(lhv, rhv))
template<class Lhv, class Rhv>
using is_swappable = or_type<is_std_swappable<Lhv, Rhv>, is_specially_swappable<Lhv, Rhv>>;

GENERATE_COMPILES_TRAIT(is_foreachable, it, std::begin(it), std::end(it))
GENERATE_COMPILES_BITRAIT(is_indexable, it, ix, it[ix])
GENERATE_COMPILES_TRAIT(is_dereferenceable, it, *it)

GENERATE_COMPILES_TRAIT(is_forward_iterator, it, 
                            *it,
                            ++it, it++, 
                            it == it, it != it
                        )
GENERATE_COMPILES_TRAIT(is_bidir_iterator, it, 
                            *it, 
                            ++it, it++, 
                            it == it, it != it, 
                            --it, it--
                        )
GENERATE_COMPILES_TRAIT(is_random_access_iterator, it, 
                            *it, 
                            ++it, it++, 
                            it == it, it != it, 
                            --it, it--, 
                            it < it, it <= it, it > it, it >= it, 
                            it - it, 
                            it - 0, it + 0, 
                            it += 0, it -= 0, 
                            it[0]
                        )
                        
namespace std {
    template<class T>
    true_type is_in_std_f(T&& val);
}
std::false_type is_in_std_f(...);
template<class T> using is_in_std = decltype(is_in_std_f(declref<T>()));

int main() { 
    static_assert(is_foreachable<std::vector<int>>::value, "");
    static_assert(is_foreachable<double[23]>::value, "");
    static_assert(!is_foreachable<double>::value, "");
    static_assert(!is_foreachable<double*>::value, "");
    
    static_assert(is_indexable<std::vector<int>, int>::value, "");
    static_assert(is_indexable<int, int*>::value, "");
    static_assert(is_indexable<int[23], int>::value, "");
    static_assert(!is_indexable<double, int>::value, "");
    static_assert(is_indexable<int*, int>::value, "");
    static_assert(is_indexable<std::map<const char*, double>, char*>::value, "");
    
    static_assert(!is_dereferenceable<std::vector<int>>::value, "");
    static_assert(is_dereferenceable<int[23]>::value, "");
    static_assert(!is_dereferenceable<double>::value, "");
    static_assert(is_dereferenceable<int*>::value, "");
    static_assert(is_dereferenceable<std::vector<int>::iterator>::value, "");
    
    static_assert(!is_random_access_iterator<int>::value, "");
    static_assert(is_random_access_iterator<int*>::value, "");
    static_assert(is_random_access_iterator<const int*>::value, "");
    static_assert(is_random_access_iterator<std::vector<int>::iterator>::value, "");
    
    std::cout << std::boolalpha << is_in_std<std::vector<int>>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<std::string>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<int>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<size_t>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<std::unique_ptr<int>>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<std::ostream>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<std::string::iterator>{} << std::endl;
    std::cout << std::boolalpha << is_in_std<std::vector<int>::iterator>{} << std::endl;

#define LAM(X, ...) [=](auto&& X){ return __VA_ARGS__; }
    
    auto s = LAM(a, LAM(b, LAM(c, ((a)(c))((b)(c)) )));
    auto k = LAM(a, LAM(b, a));
    auto i = LAM(x, x);
    auto m = (s)(i)(i);
    std::cout << (m)(i)(2) << std::endl;

}
