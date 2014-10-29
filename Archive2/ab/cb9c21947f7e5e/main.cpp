#include <initializer_list>
#include <iostream>
#include <typeinfo>

int main() {
    std::cout << R"x(
        if(x == 3) {
            for(int i = 0; i < 30; i++) {
                if(i == 3) {
                    what am I doing
                }
            }
        }
    )x" << std::endl;
}

