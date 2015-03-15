#include <list>
#include <algorithm>

int main() {
    std::list<int> list;
    std::make_heap(list.begin(), list.end());
}