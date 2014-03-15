#include <chrono>
#include <unordered_set>
#include <set>
#include <iostream>
#include <array>
#include <cstdlib>

template <std::size_t N>
int find(const std::array<char, N>& arr, int value)
{
    for(char c : arr) {
        if(value == c) {
            return static_cast<int>(c);
        }
    }
}

int find(const std::unordered_set<char>& s, int value)
{
    auto it = s.find(value);
    return static_cast<int>(*it);
}

int find(const std::set<char>& s, int value)
{
    auto it = s.find(value);
    return static_cast<int>(*it);
}

std::unordered_set<char> make_uset()
{
    std::unordered_set<char> s;
    for(char c = 'A'; c < 'Z'; ++c) {
        s.insert(c);
    }
    return s;
}

std::set<char> make_set()
{
    std::set<char> s;
    for(char c = 'A'; c < 'Z'; ++c) {
        s.insert(c);
    }
    return s;
}

int main()
{
    srand(time(nullptr));
    
    //#ifdef USE_ARRAY
        std::array<char, 27> s = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    //#elseif USE_USET
        //auto s = make_uset();
    //#elseif USE_SET
        //auto s = make_set();
    //#endif
    
    auto start = std::chrono::high_resolution_clock::now();
    for(unsigned i = 0; i < 10000000; ++i) {
        int j = find(s, static_cast<int>(rand() % 27 + 'A'));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << total << "\n";
}