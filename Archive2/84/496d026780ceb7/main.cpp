
#include <iostream>

class MyEnum {
    struct Alfa { constexpr operator int() const { return 0; } };
    struct Beta { constexpr operator int() const { return 1; } };
    int v;
public:
    constexpr static Alfa ALFA {};
    constexpr static Beta BETA {};
    MyEnum(const MyEnum&) = default;
    constexpr MyEnum(Alfa vv): v(vv) {}
    constexpr MyEnum(Beta vv): v(vv) {}
    constexpr MyEnum() : MyEnum(ALFA) {}
    operator int () const { return v; }
};

int main() {
    MyEnum a = MyEnum::BETA;
    //a = MyEnum::ALFA;
    
    switch( a ) {
        case MyEnum::ALFA:
            std::cout << "ALFA\n";
            break;
        case MyEnum::BETA:
            std::cout << "BETA\n";
            break;
    }
}
