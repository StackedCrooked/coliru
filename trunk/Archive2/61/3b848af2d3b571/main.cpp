#include <memory>
#include <iostream>

int main()
{
    std::shared_ptr<int> p;
    std::cout << std::atomic_is_lock_free(&p);
}
