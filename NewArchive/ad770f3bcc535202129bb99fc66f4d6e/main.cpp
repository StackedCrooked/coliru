#include <utility>
#include <tuple>
#include <vector>
#include <iostream>

using ullong = unsigned long long;

constexpr int gcd(ullong n,ullong m){return m==0?n:gcd(m,n%m);}

template<typename T>
std::vector<std::tuple<T,T,T>> generateTriples(ullong limit) {
    std::vector<std::tuple<T,T,T>> triples;
    for(ullong n = 1; n < limit; ++n) {
        if((n*n + (n+1) * (n+1)) > limit)
            break;
        for(ullong m = n+1; m < limit; m += 2) {
            if(n*n + m*m > limit)
                break;
            if(gcd(n,m) > 1)
                continue;
            triples.push_back(std::make_tuple(m*m-n*n,2*m*n,m*m+n*n));
        }
    }
    return triples;
}

int main() {
    std::vector<std::tuple<unsigned,unsigned,unsigned>> triples = generateTriples<unsigned>(1000);
    for(auto& i : triples)
        std::cout << "a: " << std::get<0>(i) << " b: " << std::get<1>(i) << " c: " << std::get<2>(i) << '\n';
}