#include <iostream>

int main() {
    auto lambda=[] () { std::cout << "Error occurred!" << std::endl; };

    auto lambda_2=[=/*,lambda*/] () {
        try {
            //  Do something
            std::cout << (2+2) << std::endl;
        } catch (...) {
            lambda();
            throw;
        }
    };
}
