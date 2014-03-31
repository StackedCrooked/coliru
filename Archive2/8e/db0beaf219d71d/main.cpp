#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;


void allocStack() {
    char arr[255] = {};
    arr[0] = arr[0];
}

void allocHeap() {
    char* arr = new char[255];
    arr = arr;
    delete arr;
}

int main() {
    auto b = [=](int r, void(f)()) {
        auto start = system_clock::now();
        for (int i = 0; i < r; i++) f();
        auto end = system_clock::now();
        cout << duration_cast<nanoseconds>(end-start).count() / double(r) << ", ";
    };
    for (auto& f : {allocStack, allocHeap}) {
        b(10000000, f);
    }
}