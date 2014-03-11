#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <memory>

using namespace std;

struct object {
    static unsigned cnt;
    unsigned id;
    object() : id(cnt) { ++cnt; }
    void print() const { cout << "o" << id << endl; }
};
unsigned object::cnt = 0;

int main() {
    int a[6] = {1,2,3,4,5,6};
    int b[6] = {7,8,9,10,11,12};

    for (auto i : {0,1,2,3,4,5})
      a[i] += b[i];
    for (int& e : a)
      e *= 2;
    std::vector<object> v (10);
    for (auto const& e : v)
      e.print();
}