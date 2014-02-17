#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>
using namespace std;

template<bool C, typename R =void>
using E = typename enable_if<C, R>::type;

double f(int) {return 0.0;}
int f(vector<int>);

struct subs_failure {};

template<typename T>
struct subs_succeeded {
    static constexpr bool value{true};
};

template<>
struct subs_succeeded<subs_failure> {
    static constexpr bool value{false};
};

template<typename T>
struct get_f_result {
    template<typename U>
        static auto check(const U& u) -> decltype(f(u));
    static subs_failure check(...);
    using type = decltype(check(declval<T>()));
};

template<typename T>
struct has_f : subs_succeeded<typename get_f_result<T>::type> {
};

int main() {
    int i; vector<float> v;
    get_f_result<vector<int>>::type d;
    cout << has_f<decltype(i)>::value << endl;
    if (has_f<decltype(v)>::value) f(v);
    cout << typeid(d).name() << endl;
}