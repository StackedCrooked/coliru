#include <string>
#include <iostream>

int main(){
    std::string test = "aaa";
    double a = 1.0;
    for (std::size_t j = 0; j < test.size(); ++j) {
        if (test[j] == 'a') {
            a /= (1.5 - 0.01 * j);
            std::cout << "a=" << a << '\n';
        }
    }
}