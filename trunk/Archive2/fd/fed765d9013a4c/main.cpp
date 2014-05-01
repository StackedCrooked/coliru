auto Curry=[](auto x,auto y){return[=]{auto i=x();while(i--)y();};};

#include <iostream>

int main() {
    auto foo = Curry([]{return 12;}, []{std::cout << "y\n";});
    foo();
}
