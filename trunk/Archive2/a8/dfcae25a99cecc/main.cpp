#include <string>
#include <vector>
#include <iostream>

void do_things(std::string&& str) = delete;
void do_things(const std::string& str) {
    // no error
    std::cout << str << '\n';
}

int main() {
#if defined(ERROR)
    do_things("hello");
#else
    std::string stuff = "hello";
    do_things(stuff);
#endif
}