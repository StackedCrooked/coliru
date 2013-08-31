#include <string>
#include <tuple>

std::tuple<int, std::string, char> foo() {
    return std::tuple<int, std::string, char> {1, "faagel", 'c'};
}

int main() {
    auto ret = foo();
}
