#include <type_traits>
template < typename...dummy >
class wrapper;

template < typename TYPE >
class wrapper < TYPE > {};

template < template < typename... > class TYPE, typename... PARAMS >
class wrapper < TYPE < PARAMS... > > {};

template < typename >
class templated_class {};
class normal_class {};

template <template < typename... > class T, typename... params>
wrapper<T<params...>> wrapper_helper();

template <typename T>
wrapper<T> wrapper_helper();

#define first_va(f,...) f
#define PASTE2(x, y) x##y
#define PASTE(x, y) PASTE2(x,y)
#define createwrapper(...) \
    typedef decltype(wrapper_helper< __VA_ARGS__ >())
    PASTE(first_va(__VA_ARGS__,_blank), _wrapper);

createwrapper(normal_class)
createwrapper(templated_class,int)

int main(){
    static_assert(std::is_same<wrapper<normal_class>, normal_class_wrapper>::value, "Oops");
    static_assert(std::is_same<wrapper<templated_class<int>>, templated_class_wrapper>::value, "Oops");
}