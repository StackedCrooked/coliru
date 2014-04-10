
#include <iostream>

class MyEnum {
    MyEnum* p;
    MyEnum(MyEnum* pp) : p(pp) {};
    static MyEnum A() { return MyEnum(&ALFA); }
    static MyEnum B() { return MyEnum(&BETA); }
public:
    static MyEnum ALFA;
    static MyEnum BETA;
    MyEnum(const MyEnum&) = default;
    MyEnum() : MyEnum(ALFA) {}
    constexpr operator uintptr_t () { return reinterpret_cast<uintptr_t>(p); }
};

MyEnum MyEnum::ALFA = MyEnum::A();
MyEnum MyEnum::BETA = MyEnum::B();

int main() {
    MyEnum a = MyEnum::BETA;
    
    switch( a ) {
        case MyEnum::ALFA:
            std::cout << "ALFA\n";
            break;
        case MyEnum::BETA:
            std::cout << "BETA\n";
            break;
    }
}
