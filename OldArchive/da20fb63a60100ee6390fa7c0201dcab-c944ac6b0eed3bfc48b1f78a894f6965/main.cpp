#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template<typename T>
struct X
{
    X(T t) : t(std::move(t)) {}

    T t;
};

template<typename T>
auto CreateX(const T& t) -> X<const T&>
{
    return X<const T&>(t);
}

template<typename T>
auto CreateX(T&& t) -> typename std::enable_if<!std::is_reference<T>::value,X<T>>::type
{
    return X<T>(std::move(t));
}

int main()
{
    using namespace std;
    vector<int> vec = {1,2,3,4};

    auto x1 = CreateX(vec);
    auto x2 = CreateX(vector<int>{5,6,7,8});

    cout << "x1: "; for(auto x : x1.t) cout << x << " "; cout << endl;
    cout << "x2: "; for(auto x : x2.t) cout << x << " "; cout << endl;
}
