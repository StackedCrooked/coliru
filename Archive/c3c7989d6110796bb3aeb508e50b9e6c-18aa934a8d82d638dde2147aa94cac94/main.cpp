#include <type_traits>

template<class T>
struct trait{ using type = typename T::type; };

template<class T, class U = typename trait<T>::type>
void f(int);
void f(...);

template<class T, class U = typename T::type>
void g(int);
void g(...);

template<class>
struct dependent_false : std::false_type{};

template<class T>
struct X{
    static_assert(dependent_false<T>(), "...");
    using type = void;
};

int main(){
    f<int>(0);
    g<X<int>>(0);
}