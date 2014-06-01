#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    
    {
        auto p = high_resolution_clock::now();
        int arr[1000000];
        nanoseconds t = high_resolution_clock::now() - p;
        std::cout << "Static: " << t.count() << " nanoseconds.\n";
    }
    
    {
        auto p = high_resolution_clock::now();
        int* arr = new int[1000000];
        nanoseconds t = high_resolution_clock::now() - p;
        std::cout << "Dynamic: " << t.count() << " nanoseconds.\n";
    }
    
    return 0;
}