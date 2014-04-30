auto Curry=[](auto x,auto y){return[=]{for(auto i=x();i--;y());};};

#include <iostream>

using std::cout;

int main() {
    auto x = [](){ return 8; };
    auto y = [](){ cout << "test "; };
    auto g = Curry(x, y);
    g();
}
