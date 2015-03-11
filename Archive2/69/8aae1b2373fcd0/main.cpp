#include <memory>
#include <functional>
#include <iostream>
#include <boost/signals2/signal.hpp>

template<typename T>
using erased_deleter = std::function<void(T*)>;

template<typename T>
using erased_unique_ptr = std::unique_ptr<T, erased_deleter<T>>;

template<typename T, typename... Args>
erased_unique_ptr<T> make_erased_unique(erased_deleter<T> deleter, Args&&... args)
{
    return erased_unique_ptr<T>{new T{std::forward<Args>(args)...}, std::move(deleter)};
}

struct X
{
};

struct factory
{
    erased_unique_ptr<X> make_x()
    {
        return make_erased_unique<X>([this] (X* x) { dispose_x(x); });
    }
    
    void dispose_x(X* x)
    {
        _on_before_deleting_x(*x);
        delete x;
    }

    void register_x_deletion_handler(std::function<void(X&)> f)
    {
        _on_before_deleting_x.connect(std::move(f));
    }

private:

    boost::signals2::signal<void(X&)> _on_before_deleting_x;
};

int main()
{
    auto f = factory{};
    auto p = f.make_x();
    
    f.register_x_deletion_handler([] (X&) { std::cout << "Deleting X" << std::endl; });
}