#include <algorithm>
#include <atomic>
#include <cassert>
#include <iostream>
#include <list>

std::list<std::atomic<int>> lst;

void print() {
    for (const auto& i : lst) {
        std:: cout << i << ' ';
    }
    std::cout << '\n';
}

int main() {
    lst.emplace_back(42);
    lst.emplace_back(13);
    lst.emplace_front(11);
    print();
    auto pos = std::find_if(begin(lst), end(lst), [](const std::atomic<int>& i){ return i == 13; });
    assert(pos != lst.end());
    ++*pos;
    print();
}
