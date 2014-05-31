#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    
    {
        auto p = high_resolution_clock::now();
        int arr[1000000];
        auto t = duration_cast<nanoseconds>(high_resolution_clock::now() - p).count();
        std::cout << "Static: " << t << " nanoseconds.\n";
    }
    
    {
        auto p = high_resolution_clock::now();
        int* arr = new int[1000000];
        auto t = duration_cast<nanoseconds>(high_resolution_clock::now() - p).count();
        std::cout << "Dynamic: " << t << " nanoseconds.\n";
    }
    
    return 0;
}