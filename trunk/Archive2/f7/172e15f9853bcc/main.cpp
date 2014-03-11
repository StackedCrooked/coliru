#include <string.h>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <mutex>
#include <tuple>
#include <string>
#include <sstream>

using namespace std;

string to_string(const char* s)
{
    return s;
}

string to_string(string s)
{
    return s;
}

// C++14
template<typename... T>
auto to_tuple_of_string(T&&... args)
{
    return make_tuple(to_string(args)...);
}

// C++11
template<typename... T>
auto foo(T&&... args) -> decltype(make_tuple(to_string(args)...))
{
    return make_tuple(to_string(args)...);
}

int main()
{
    auto tt = foo("hello", 10, 1.0);
    cout << get<0>(tt) << endl;
    cout << get<1>(tt) << endl;
    cout << get<2>(tt) << endl;
}
