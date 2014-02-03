#include <iostream>
#include <functional>


std::function<int(int)> returnFunction(){
    int myLocal = 2;
    std::function<int(int)> ret = [&myLocal](int i){myLocal++;return i+myLocal;};
    return ret;
}

int main() {
    auto lambda = returnFunction();
    std::cout << lambda(2) << "\n";
    std::cout << lambda(4) << "`\n";
    return 0;
}