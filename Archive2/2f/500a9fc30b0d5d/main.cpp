#include <tuple>

int main() {
    std::tuple<double> foo = 0.11;
    return std::get<0>(foo);
}
