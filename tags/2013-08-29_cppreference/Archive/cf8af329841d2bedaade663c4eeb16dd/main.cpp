#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using ullong = unsigned long long;
ullong nCr(ullong n, ullong k){
    if (k > n) 
        return 0;
    if (k * 2 > n) 
        k = n-k;
    if (k == 0) 
        return 1;

    ullong result = n;
    for(ullong i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

constexpr ullong gcd(ullong x, ullong y) {
    return (y == 0) ? x : gcd(y,(x%y));
}

template<typename T>
std::vector<std::pair<T,T>> generateTriples(ullong limit) {
    std::vector<std::pair<T,T>> triples;
    ullong a, b;
    for(ullong n = 1; n < limit; ++n) {
        if(n*n + (n+1)*(n+1) > limit)
            break;
        for(ullong m = n+1; m < limit; m += 2) {
            if(n*n + m*m > limit)
                break;
            if(gcd(n,m) > 1)
                continue;
            a = m*m - n*n;
            b = 2*m*n;
            if(a*a > limit || b*b > limit)
                break;
            else {
                triples.push_back(std::make_pair(a*a,b*b));
                triples.push_back(std::make_pair(b*b,a*a));
            }
        }
    }
    return triples;
}

/*
101 101
5151 5151
176851 176851
4598126 4598126
96560646 96560646
1705904746 1705904746
26075972546 26075972546
352025629371 352025629371
*/

ullong P(ullong n, ullong m, std::vector<std::pair<ullong, ullong>> points){
    std::vector<ullong> A(n+1);  
    std::fill(A.begin(),A.end(),1);
    points.push_back(std::make_pair(0,0));
    ullong k=0;
    
    
    for(ullong i=1; i<=n; i++) {
           for(ullong j=1; j<=n; j++) {
               if(std::make_pair(i,j) == points[k]) {
                  A[j]=0;    
                  k+=1;  
               }
               else {
                   A[j]=(A[j]+A[j-1]) % m;
               }
           }
    }
    return A[n] % m;
}
ullong P(ullong n, std::vector<std::pair<ullong, ullong>> points) {
    std::vector<ullong> A(n+1);  
    std::fill(A.begin(),A.end(),1);
    points.push_back(std::make_pair(0,0));
    ullong k=0;
    
    
    for(ullong i=1; i<=n; i++) {
           for(ullong j=1; j<=n; j++) {
               if(std::make_pair(i,j) == points[k]) {
                  A[j]=0;    
                  k+=1;  
               }
               else {
                   A[j]=(A[j]+A[j-1]);
               }
           }
    }
    return A[n];
}
int main() {
    std::vector<std::pair<ullong,ullong>> triples = generateTriples<ullong>(16);
    for(auto& i : triples)
        std::cout << i.first << " " << i.second << '\n';
    std::cout << P(16,triples);
}

