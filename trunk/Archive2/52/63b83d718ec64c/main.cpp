#include <memory>
#include <type_traits>
#include <cstdlib>

template<typename Element, typename Deleter>
std::unique_ptr<Element, typename std::decay<Deleter>::type> make_unique_with_deleter(Element* data, Deleter&& deleter)
{ return { data, std::forward<Deleter>(deleter) }; }

int main()
{
    auto p = make_unique_with_deleter(std::malloc(42), [](void* p) { std::free(p); });
}