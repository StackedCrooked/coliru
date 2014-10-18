#include <iostream>
#include <utility>

using namespace std;

class Hoge
{
    void func()
    {
    }
};

template <typename T>
struct has_func
{
    template <typename U>
    static auto type_check(U obj) -> decltype(obj.func(), true_type());
    static auto type_check(...) -> false_type;

    using type = decltype(type_check(declval<T>()));
};

int main()
{ 
    cout << "Hoge has " << (has_func<Hoge>::type::value ? "func" : "not func") << endl;
}