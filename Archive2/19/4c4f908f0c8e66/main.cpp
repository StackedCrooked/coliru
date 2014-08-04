#include <iostream>
#include <string>

int main() {
    std::string quoted = R"("Foo said, \"bar\"\n")";
    std::cout << quoted;
}
