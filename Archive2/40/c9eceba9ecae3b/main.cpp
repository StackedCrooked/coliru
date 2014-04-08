#include <fstream>
#include <iostream>

int main() {
    std::fstream foo;
    std::ostream& bar = foo;
    bar.rdbuf(std::cout.rdbuf());
    return 0;
}
