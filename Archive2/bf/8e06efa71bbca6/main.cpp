#include <fstream>

struct A {
    
};

int main(int, char **argv) {
    A a(std::fstream(argv[1]));    
}
