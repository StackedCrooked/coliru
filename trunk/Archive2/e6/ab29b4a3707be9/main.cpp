#include <string>
#include <set>

using namespace std;

using Atom = const char*;

template <typename... Args>
typename enable_if<
    is_constructible<string, Args...>::value, Atom
>::type make_atom(Args&&... args)
{
    static set<string> interned;
    return interned.emplace(forward<Args>(args)...).first->c_str();
}

#include <iostream>

int main() {
    std::cout << make_atom("Hello World\n");
    std::cout << make_atom(80, '=');
}
