#include <cstddef>

struct PointerProxy {
    PointerProxy() {}
    
    operator int*() {
        return NULL;
    }
    
    operator double*() {
        return NULL;
    }
};

PointerProxy get_array_pointer() {
    return PointerProxy();
}

int main() {
    int *i = get_array_pointer();
    double *d = get_array_pointer();
}