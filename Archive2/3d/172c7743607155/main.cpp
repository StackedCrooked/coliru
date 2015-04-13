#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <random>
#include <chrono>
using namespace std;

static const size_t N = 1000000; //size of the arrays
static const size_t REPS = 1000; //number of repitions

std::array<double, N> a1;
std::array<double, N> a2;

void testSTD() {
    std::cout << "STD\t";
    auto start=std::chrono::high_resolution_clock::now();
    double res = 0.0;
    for (size_t z = 0; z < REPS; z++) {
        res = std::inner_product(a1.begin(), a1.end(), a2.begin(), res);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << res << '\t' << dur.count() << '\n';
}
void testManual() {
    std::cout << "Manual\t";
    auto start=std::chrono::high_resolution_clock::now();
    double res = 0.0;
    for (size_t z = 0; z < REPS; z++) {
        for (size_t t = 0; t < N; ++t)  {
            res += a1[t] * a2[t];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << res << '\t' << dur.count() << '\n';
}

int main(){
    srand(10);
    for (size_t i = 0; i < N; ++i)
        a1[i] = static_cast<double>(rand())*0.01;
    for (size_t i = 0; i < N; ++i)
        a2[i] = static_cast<double>(rand())*0.01;

    testSTD();
    testSTD();
    testSTD();
    testSTD();
    testSTD();
    testManual();
    testManual();
    testManual();
    testManual();
    testManual();
    testSTD();
    testSTD();
    testSTD();
    testSTD();
    testSTD();

    std::cin.get();
    return 0;
}