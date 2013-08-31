#include <vector>
#include <iostream>

template<class Cont, class Callable>
void for_each(Cont&& cont, Callable f) {
    for(auto&& i : cont) {
        f(i);
    }
}

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7};
    for_each(v, [](int a) { std::cout << a << ' '; });
}