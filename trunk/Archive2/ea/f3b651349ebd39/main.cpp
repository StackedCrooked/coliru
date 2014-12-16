#include <iostream>

int main() {
    std::cout<<"Hello world"<<std::endl;
    std::cout.operator<<("Hello world").operator<<(std::endl);
    return 0;
}
