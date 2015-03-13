#include <memory>
#include <functional>
#include <cassert>

template<typename Func, typename Item>
std::function<bool()> foo(Func func, std::shared_ptr<Item> item)
{
    std::weak_ptr<Item> w = item;
    return [w, func]
    {
        if(auto i = w.lock()) {
            // ideally:
            // std::invoke(func, *i);
            func(*i);
            return true;
        } else {
            return false;
        }
    };
}

int main()
{
    auto p = std::make_shared<int>();
    assert( foo([](int) {}, p)() );
    assert( foo([](int) {}, p)() );
    p.reset();
    assert( !foo([](int) {}, p)() );
}