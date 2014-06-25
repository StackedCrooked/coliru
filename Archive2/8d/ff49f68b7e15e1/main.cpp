#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<class T, class FieldT>
using addRefU = typename std::conditional<
                            std::is_rvalue_reference<T>::value,
                            typename std::add_rvalue_reference< FieldT >::type,
                            typename std::conditional<
                                std::is_rvalue_reference<FieldT>::value,
                                typename std::add_rvalue_reference< FieldT >::type,
                                typename std::add_lvalue_reference< FieldT >::type
                            >::type
                        >::type;
                        
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 4, 3, 2, 1, 0)
#define VARARG_IMPL2(base, count, ...) base##count(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL2(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)
                        

#define REF2(val, p1) addRefU<decltype(val), decltype(val.p1)>
#define REF3(val, p1, p2) addRefU<decltype(val), decltype(val.p1.p2)>
#define REF4(val, p1, p2, p3) addRefU<decltype(val), decltype(val.p1.p2.p3)>
#define REF5(val, p1, p2, p3, p4) addRefU<decltype(val), decltype(val.p1.p2.p3.p4)>
#define REF(...) VARARG(REF, __VA_ARGS__)



#define CAST_REF2(val, p1) static_cast<REF(val, p1)>(val.p1)
#define CAST_REF3(val, p1, p2) static_cast<REF(val, p1, p2)>(val.p1.p2)
#define CAST_REF4(val, p1, p2, p3) static_cast<REF(val, p1, p2, p3)>(val.p1.p2.p3)
#define CAST_REF5(val, p1, p2, p3, p4) static_cast<REF(val, p1, p2, p3, p4)>(val.p1.p2.p3.p4)
#define CAST_REF(...) VARARG(CAST_REF, __VA_ARGS__)


struct A{};
struct B{A a;};
       
int main()
{
    B b;
    
    using t = REF(b, a);    // Ok
    
    auto &&k = CAST_REF2(b, a); // work
    auto &&k1 = CAST_REF(b, a); // NOT work
    
    return 0;
}
