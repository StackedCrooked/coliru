#include <iostream>

using ret = float(&)[3];

struct Vector {
    float x, y, z;
    operator ret() { 
        return reinterpret_cast<float(&)[3]>(*this);
    }
};

int main(int, char*[]) {
    return 0;
}