#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using ll = long long;
constexpr ll maxSize = 10 * 10 * 10 * 10 * 10;
constexpr ll modulos = 1e9 + 7;
int pfactors[] =
{
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317
};

void factors(int value, std::unordered_map<int, int> &lcm) {
    for (const int *v = pfactors; (*v) * (*v) <= value; v++) {
        int c = 0;
        for ( ; value % *v == 0; c++)
            value /= *v;
            
        if (c) {
            int *p = &lcm[*v];
            *p = std::max(*p, c);
        }
    }
    
    if (value > 1) {
        int *p = &lcm[value];
        *p = std::max(*p, 1);
    }
}

ll solve(const int *array, int size) {
    std::unordered_map<int, int> lcm;
    for (int fin = 0; fin < size; fin++) {
        int count = 1;
        for (int b = array[fin]; b != fin; b = array[b]) {
            count++;
        }
        factors(count, lcm);
    }
    ll ans = 1;
    for (auto &v : lcm) {
        ans = (ans * static_cast<ll>(std::pow(v.first, v.second))) % modulos;
    }
    return ans;
}

int main() {
   int T, N, bandits[maxSize];
   for (std::cin >> T; T--; ) {
        std::cin >> N;
        for (int v = 0; v < N; v++) {
            std::cin >> bandits[v];
            --bandits[v];
        }
        std::cout << solve(bandits, N) << '\n';
    }

    return 0;
}

/**NOT USED**/
inline ll gcd(ll a, ll b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    ll temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}