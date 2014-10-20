#include <iostream>
#include <array>
#include <map>

using DelegateKey = std::array<std::uintptr_t, 2>;

template <typename T_rv> class Function;
template <typename T_rv, typename... Args>
struct Function<T_rv(Args...)>
{

    using Thunk = T_rv(*)(void*, Args...);

    void* m_this_ptr; // instance pointer
    Thunk m_stub_ptr; // free function pointer

    template <T_rv (*fun_ptr)(Args...)>
    static inline Function bind()
    {
        return { nullptr, [](void* /*NULL*/, Args... args) {
        return (*fun_ptr)(std::forward<Args>(args)...); }};
    }

    inline operator DelegateKey() const
    {
        return
        {
            reinterpret_cast<std::uintptr_t>(m_this_ptr),
            reinterpret_cast<std::uintptr_t>(m_stub_ptr)
        };
    }
};

class Observer
{
    template <typename T> friend class Signal;

    std::map<DelegateKey, Observer*> tracked_connections;

    void insert(DelegateKey const& key)
    {
        tracked_connections.emplace(key, this);
    }
    void remove(DelegateKey const& key)
    {
        tracked_connections.erase(key);
    }

    protected:

   ~Observer()
    {
        auto iter = tracked_connections.cbegin();
        auto stop = tracked_connections.cend();

        while (iter != stop)
        {
            auto const& delegate_key = iter->first;
            auto const& observer = iter->second;

            std::advance(iter, 1);

            observer->remove(delegate_key);
        }
    }
};


template <typename T_rv> class Signal;
template <typename T_rv, typename... Args>
class Signal<T_rv(Args...)> : private Observer
{
    public:

    using Delegate = Function<T_rv(Args...)>;

    template <T_rv (*fun_ptr)(Args...)>
    void connect()
    {
        Observer::insert(Delegate::template bind<fun_ptr>());
    }
};

//------------------------------------------------------------------------------

void test(std::size_t const& a)
{
    std::cout << "[Test] caller line: " << a << std::endl;
}

int main()
{
    Signal<void(std::size_t)> sig;

    sig.connect<test>();
}
