#include <algorithm>
#include <iostream>

void* operator new (std::size_t n) {
    std::cout << "Here\n";
    auto p = malloc(n);
    std::fill_n((char*)p, n, 'a');
    return p;
}

int main() {
    int *ipa = new int[5]{1, 2, 3};
    std::for_each(ipa, ipa + 5, [](int i) {
        std::cout << i << '\n';
    });
}
