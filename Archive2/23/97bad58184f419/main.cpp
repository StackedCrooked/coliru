#include <iostream>

struct vector {
    float x, y, z;
};

auto stupid_func(vector& v) -> float(&)[3] {
    return reinterpret_cast<float(&)[3]>(v);
}

int main(int, char*[]) {
    vector x; x.x = 123;
    std::cout << stupid_func(x)[0];
    return 0;
}