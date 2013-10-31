    #include <cstdlib>
    #include <cmath>
    #include <cstdint>
    #include <iostream>
    #include <sstream>
    #include <set>
    #include <iterator>
    #include <algorithm>
    #include <iostream>
    #include <chrono>
     
    using namespace std;
     
    const auto n = 10000000ULL; // constexptr is tested, no effect
     
    int main() {
    {
    auto t1 = std::chrono::high_resolution_clock::now();
     
    std::string s;
     
    for (auto i = 0ULL; i < n; i++)
    s += "1234567890";
     
    auto x = s.length();
     
    auto t2 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    cout << "Result: " << x << " -- time (ms):" << t / 0.1e7 << endl;
    }
     
    auto t1 = std::chrono::high_resolution_clock::now();
     
    std::ostringstream ss;
     
    for (auto i = 0ULL; i < n; i++)
    ss << "1234567890";
     
    auto x = ss.str().length();
     
    auto t2 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    cout << "Result: " << x << " -- time (ms):" << t / 0.1e7 << endl;
    }