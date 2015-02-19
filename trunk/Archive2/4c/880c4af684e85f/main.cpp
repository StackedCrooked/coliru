#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <array>
#include <memory>

namespace Nano
{

using DelegateKey = std::array<std::uintptr_t, 2>;

template <typename T_rv> class Function;
template <typename T_rv, typename... Args>
class Function<T_rv(Args...)>
{
    template <typename T> friend class Signal;

    using Thunk = T_rv(*)(void*, Args...);

    void* m_this_ptr; // instance pointer
    Thunk m_stub_ptr; // free function pointer

    template <typename T, typename F>
    Function (T&& this_ptr, F&& stub_ptr):
        m_this_ptr { std::forward<T>(this_ptr) },
        m_stub_ptr { std::forward<F>(stub_ptr) } {}

    Function (DelegateKey const& _k):
        m_this_ptr { reinterpret_cast<void*>(std::get<0>(_k)) },
        m_stub_ptr { reinterpret_cast<Thunk>(std::get<1>(_k)) } {}

    public:

    template <typename T, T_rv (T::*mem_ptr)(Args...)>
    static inline Function bind(T* pointer)
    {
        return { pointer, [](void* this_ptr, Args... args) {
        return (static_cast<T*>(this_ptr)->*mem_ptr)
            (std::forward<Args>(args)...); }};
    }

    inline T_rv operator() (Args... args)
    {
        return (*m_stub_ptr)(m_this_ptr, std::forward<Args>(args)...);
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

    void insert(DelegateKey const& key, Observer* observer)
    {
        tracked_connections.emplace(key, observer);
    }
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
    template <typename T>
    void insert_sfinae(DelegateKey const& key, typename T::Observer* instance)
    {
        Observer::insert(key, instance);
        instance->insert(key, this);
    }
    template <typename T>
    void remove_sfinae(DelegateKey const& key, typename T::Observer* instance)
    {
        Observer::remove(key);
        instance->remove(key);
    }
    template <typename T>
    void insert_sfinae(DelegateKey const& key, ...)
    {
        Observer::insert(key);
    }
    template <typename T>
    void remove_sfinae(DelegateKey const& key, ...)
    {
        Observer::remove(key);
    }

    public:

    using Delegate = Function<T_rv(Args...)>;

    template <typename T, T_rv (T::*mem_ptr)(Args...)>
    void connect(T* instance)
    {
        auto delegate  = Delegate::template bind<T, mem_ptr>(instance);
        insert_sfinae<T>(delegate, instance);
    }

    void operator() (Args... args)
    {
        for (auto const& slot : tracked_connections)
        {
            Delegate(std::get<0>(slot))(std::forward<Args>(args)...);
        }
    }
};

} // namespace Nano ------------------------------------------------------------

class X
{

public:

    Nano::Signal<void(X *x, std::shared_ptr<int> n)> onNumber;

public:

    void emit()
    {
        auto n(std::make_shared<int>(12));
        onNumber(this, n);
    };
};

class A
{
public:

    void SetupHandler(X *x)
    {
        x->onNumber.connect<A, &A::HandleNumber>(this);
    }

private:

    void HandleNumber(X *x, std::shared_ptr<int> n)
    {
        std::cout << x << std::endl << this << std::endl << *n << std::endl;
    }
};

int main(int argc, const char * argv[])
{
    std::unique_ptr<X> x(new X);

    std::unique_ptr<A> a1(new A);
    
    a1->SetupHandler(x.get());

    std::unique_ptr<A> a2(new A);
    
    a2->SetupHandler(x.get());

    x->emit();
}
