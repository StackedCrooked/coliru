#include <iostream>
#include <iomanip>


int main() {
    auto& me = std::cout;
    me << std::put_money("$1,000,000,000", true);
}
