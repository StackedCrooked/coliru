#include <atomic>
#include <cassert>
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr < int > a;

    std::shared_ptr < int > b;
    std::shared_ptr < int > c = std::make_shared < int > (10);

    while(atomic_compare_exchange_weak(&a, &b, c))
      ;

    assert(atomic_load(&a) == c);  
    assert(atomic_load(&a).use_count() == 2);
}
