#include <iostream>
#include <string>
#include <functional>

template<typename Func, typename = typename std::result_of<Func()>::type>
void asdf(Func doThing) {
    auto val = doThing();
}


int main()
{
    asdf([&]() {
        return std::string { "qwer" };
    });
    // rejected
    asdf([](int) {});
    return 0;
}


