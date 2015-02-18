#include <memory>
#include <iostream>

struct CAT
{
   CAT(){}
   CAT(const CAT&) {std::cout << "COPY";}
   CAT(CAT&&) {std::cout << "COPY";}
};

int main() {
    const CAT cat;
    CAT cat2 = std::move(cat);
    (void)cat2;
}