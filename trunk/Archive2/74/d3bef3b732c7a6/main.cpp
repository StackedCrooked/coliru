#include <iostream>
#include <vector>

struct asdf {
    explicit asdf(std::vector<int> things) {
        std::cout << things[0] << std::endl;
    }
};

int main() {
    asdf a = asdf({ 4, 5, 6});
    return 0;
}