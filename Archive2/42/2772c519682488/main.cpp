#include <memory>
#include <cassert>

int main()
{
    assert(std::get_pointer_safety() == std::pointer_safety::relaxed);
}