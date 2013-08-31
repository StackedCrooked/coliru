#include <utility>


int func(int&& i) {
    return 1234;
}


int main() {
    int i = 1234;
    decltype(func(std::declval<int&>())) x = func(i);
}