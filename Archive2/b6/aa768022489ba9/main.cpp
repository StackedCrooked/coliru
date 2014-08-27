// C API here

struct c_api {
    int x;
    int y;
    int z;
};

int do_calculation(struct c_api* stuff) {
    return stuff->x + 10;
}

// more fancy C API things

// end of C API

// C++ API to wrap it around all nice and fancy

struct fancy {
    int x;
    int y;
    int z;
    
    int do_calculation() {
        // delegate over to C API land
        return ::do_calculation(reinterpret_cast<c_api*>(this));
    }
};

#include <iostream>

int main() {
    fancy t = { 1, 2, 3 };
    std::cout << t.do_calculation() << '\n';
}