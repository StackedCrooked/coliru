#include <iostream>
#include <set>
#include <vector>

struct A {
    int a;
    bool operator<(A const &other) const { return a < other.a; }
};

int main() {
    std::vector<A> const a1;
    std::set<std::vector<A> > myset{ 
        { { 4 }, { 7 }, { 9 } },
        { { 5 }, { 8 }, { 10 } },
        { { 6 }, { 9 }, { 11 } },
    };

    auto it = myset.find({ {1}, {2}, {3} });
    std::cout << "Found vector: " << std::boolalpha << (it != myset.end()) << "\n"; 

    it = myset.find({ {5}, {8}, {10} });
    std::cout << "Found vector: " << std::boolalpha << (it != myset.end()) << "\n"; 
}
