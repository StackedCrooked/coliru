#include <iostream>

struct X{
    X(){ throw "shit"; }
};

struct Y{
    X x;
    Y() try : x() {
        std::cout << "nothing\n";
    } catch(...) {
        std::cout << "exception\n";
    }
};

int main(){
    try {
        Y y;
    } catch(...) {
        std::cout << "outer exception\n";
    }
}