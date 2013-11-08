#include <map>
#include <gmpxx.h>
#include <iostream>

struct Equaler {
    inline bool operator()(const mpz_class a, const mpz_class b) const {
        std::cout << " about to return " << a << "," << b << "," << cmp(a,b) << "\n";
        return cmp(a, b);
    }
};

int main() {
    mpz_class x("38268");
    std::map<mpz_class,int,Equaler> map;
    map.insert(std::pair<mpz_class,int>(x,42));
    map.find(x);
    return 0;
}