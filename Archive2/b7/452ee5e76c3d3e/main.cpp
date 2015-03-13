#include <memory>
#include <functional>
#include <cassert>

template<typename Func, typename Item, typename... Args>
std::function<bool()> foo(Func f, std::shared_ptr<Item> item, Args&&... args)
{
    std::weak_ptr<Item> w = item;
    auto bound = std::bind(f, item.get(), std::forward<Args>(args)...);
    return [w, bound]
    {
        if(auto i = w.lock()) {
            static_cast<void>(i);
            bound();
            return true;
        } else {
            return false;
        }
    };
}

int main()
{
    struct example {
        void bar(int, double) {}
    };
    auto p = std::make_shared<example>();
    assert( foo(&example::bar, p, 0, 0.)() );
    assert( foo(&example::bar, p, 0, 0.)() );
    p.reset();
    assert( !foo(&example::bar, p, 0, 0.)() );
}