#include <type_traits>
#include <string>

template <class First> // arguments ommited for brevity
struct MyClass {
    template<
        typename U = First,
        typename = typename std::enable_if< std::is_same<U, std::string>::value >::type
    >
    void f() {}
};

int main()
{
    MyClass<int> c1;
    MyClass<std::string> c2;
    // c1.f();
    c2.f();
}