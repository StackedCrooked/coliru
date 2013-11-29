#include <iostream>
#include <type_traits>
#include <string>

template <typename T = const char*>
void func(typename std::enable_if<!strcmp(T(), "I'm gay"), void>::type* = nullptr) {
}

int main ()
{
    func("I'm gay");
}
                                                        