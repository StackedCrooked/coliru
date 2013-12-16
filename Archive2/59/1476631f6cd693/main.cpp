#include <iostream>

struct Base {
    void h() {std::cout << "All your base are belong to us.\n";}
};

struct Derived : Base {
    void h() {std::cout << "Derived\n";}
};

int main() {
    Derived myderived;
    myderived.Base::h(); //compiles in VC12
    myderived.Base::Base::h(); //error in VC12
    myderived.Base::Base::Base::Base::Base::Base::h(); //error in VC12
    Base mybase;
    mybase.Base::h(); //compiles in VC12
    mybase.Base::Base::h(); //error in VC12
    mybase.Base::Base::Base::Base::Base::Base::h(); //error in VC12
}