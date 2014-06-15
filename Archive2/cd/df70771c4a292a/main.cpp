#include <tuple>

void func(std::pair<int, int>){}

int main() {
    func({1, 2});
}