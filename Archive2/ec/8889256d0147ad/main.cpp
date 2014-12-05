#include <cstdint> 

int i[100];

std::size_t get_size(int a[]) {
    return sizeof a;
}

#include <cassert>

int main() {
    assert(get_size(i) == sizeof i);
}