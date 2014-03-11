#include <type_traits>
#include <iostream>

struct test {
    test() {
        std::cout << std::is_same<decltype(this), test*>::value;
    }
};
        

int main(){
    test a;
    const test b;
}
