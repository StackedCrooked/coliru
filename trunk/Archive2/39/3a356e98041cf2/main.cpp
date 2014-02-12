#include <fstream>

struct A {};

int main(int argc, char** argv) {
    A a(std::fstream(argv[1]));
}
