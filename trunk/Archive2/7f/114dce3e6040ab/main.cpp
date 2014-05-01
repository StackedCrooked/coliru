auto Curry=[](auto x,auto y){return[=]{for(auto i=x();i--;y());};};

#include <iostream>

int main() {
    auto foo = Curry([]{return 2;}, []{std::cout << "y\n";});
    foo();
}
