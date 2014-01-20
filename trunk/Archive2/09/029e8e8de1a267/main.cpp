#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>

typedef std::chrono::time_point<std::chrono::system_clock> SystemClock;

// Sum of proper divisors
int d(int n) {
    int sum = 0;
    for(int i = 1; i < n; i++)
        if(!(n%i))
            sum+=i;
    return sum;
}

int main() {
    SystemClock begin = std::chrono::system_clock::now();
    int count = 0;
    for(int i = 0; i < 10000; i++)
        if(d(d(i))==i&&d(i)!=i)
            count+=i;
    std::cout << "Count: " << count << std::endl;
    std::cout << "Time: " << ((std::chrono::duration<double, std::milli>)(std::chrono::system_clock::now() - begin)).count() << " ms" << std::endl;
}
