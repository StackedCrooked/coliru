#include <tuple>
#include <vector>

int main() {
    std::vector<std::tuple<int, int, int>> v = {
        std::make_tuple(1,2,3), std::make_tuple(4,5,6), std::make_tuple(7,8,9)
    };
}