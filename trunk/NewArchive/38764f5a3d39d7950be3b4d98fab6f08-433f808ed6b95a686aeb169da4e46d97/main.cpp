#include <iostream>

int main() {
    int value = 1;
    int&  lref = value;
    int&& rref = std::move(value);
    auto lambda = [=,&lref,&rref](){std::cout<<value<<lref<<rref;};
    auto copy = lambda;
}