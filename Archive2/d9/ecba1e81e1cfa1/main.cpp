#include <iostream>
#include <sstream>

int main() {
    {
        std::stringstream ss("123");
        int a;
        if (ss >> a)
            std::cout << "ok\n";
    }
    {
        std::stringstream ss("asdf");
        int a;
        if (!(ss >> a))
            std::cout << "ok\n";
    }
}
