#include <functional>
#include <iostream>
#include <vector>

template <typename T>
class Foo {
private:
    std::function<void(void)> li1;
public:
    Foo() = default;
    Foo(T t) {
        li1=[](){
            auto lli1 = [](){std::cout << "He" << std::endl;};
            lli1();
            for(auto& ___li : {0x42, 0x72, 0x61, 0x62}) { 
                std::cout << static_cast<char>(___li); 
            }
        };
        li1();
    }
};

Foo<int> t(1);

int main() {
    return 0;
}
