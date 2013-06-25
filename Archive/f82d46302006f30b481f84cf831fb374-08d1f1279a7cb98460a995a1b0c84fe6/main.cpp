#include <future>
#include <iostream>


int main() {    
    std::future<int> result( std::async([](int m) { return m+1;}, 2));
    std::cout << "In main" << std::endl;
    std::cout << result.get();
}
