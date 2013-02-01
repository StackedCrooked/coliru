#include <functional>
#include <vector>

int main() {
    int i;
    int i2;
    std::vector<std::reference_wrapper<int>> v{i, i2};
}