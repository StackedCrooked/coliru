#include <cassert>
#include <functional>
#include <memory>

struct erased_deleter
{

public:

    erased_deleter(std::function<void()> handler) 
        : _handler{std::move(handler)}
    {
    }
    
    template<typename T>
    void operator () (T* const)
    {
        _handler();
    }
   
private:

    std::function<void()> _handler;

};

template<typename T>
using unique_handle = std::unique_ptr<T, erased_deleter>;

template<typename T, typename U, typename... Args>
unique_handle<T> make_unique_handle(U handler, Args&&... args)
{
    auto p = new T{std::forward<Args>(args)...};
    
    return unique_handle<T>{p, erased_deleter{[p, handler] { handler(p); }}};
}

int main()
{
    auto const i = 42;

    auto invoked = false;
    auto deleter = [&invoked, i] (int* const p) 
    { 
        assert(*p == i);
        invoked = true;
        delete p;
    };

    {
        auto p = make_unique_handle<int>(deleter, i);
        assert(*p == i);
    }

    assert(invoked);
}