#include <cstddef>
#include <iostream>

using namespace std;

template <typename ... Ts>
size_t test(Ts ... arguments) {
    int array[] = {arguments...};
    for(auto i : array)
      cout << '[' << i << "]\n";
    return sizeof...(arguments);
}

int main() {
    test(3, 1, 4, 2, 5, 0);
}
