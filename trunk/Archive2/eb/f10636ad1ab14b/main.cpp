#include <iostream>

class Test {
    public:
        Test() {
            std::cout << "I'm being constructed!\n";
        }
};

void try_me() {
    static Test t;
}

int main() {
    try_me();
    try_me();
    try_me();
    try_me();
    try_me();
    try_me();
    try_me();
    try_me();
    try_me();
    return 0;
}