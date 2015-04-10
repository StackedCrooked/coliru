#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<class... Args>
class SafeCallback
{
public:
    SafeCallback()
    {
    }
    
    template <typename T>
    SafeCallback(T&& f)
    //: _f(std::forward<T>(f))
    {
        std::cout << "SafeCallback(T&& f)" << std::endl;
    }
    
    SafeCallback(SafeCallback&& other) = default;
    SafeCallback(SafeCallback& other) = default;
    SafeCallback(const SafeCallback& other) = default;
    SafeCallback& operator=(const SafeCallback& other) = default;
    SafeCallback& operator=(SafeCallback& other) = default;
    SafeCallback& operator=(SafeCallback&& other) = default;

    template<class... T>
    void operator()(T&&... args) const
    {
        if (_f)
        {
            _f(std::forward<T>(args)...);
        }
    }
    
    explicit operator bool() const
    {
        return (bool)_f;
    }
    
    bool operator ==(std::nullptr_t) const
    {
        return _f == nullptr;
    }
    
    bool operator !=(std::nullptr_t) const
    {
        return _f != nullptr;
    }
    
    operator std::function<void(Args...)>&()
    {
        return _f;
    }
    
    operator const std::function<void(Args...)>&() const
    {
        return _f;
    }
    
private:
    std::function<void(Args...)> _f;
};

struct Noisy
{
  Noisy() { std::cout << "Noisy()" << std::endl; }
  Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
  Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
  ~Noisy() { std::cout << "~Noisy()" << std::endl; }
};

void foo(Noisy n)
{
  std::cout << "foo(Noisy)" << std::endl;
}

int main()
{
  //Noisy n;
  //SafeCallback<Noisy> f = foo;
  //f(n);
  
  SafeCallback<> cb1 = foo;
  SafeCallback<>&& cb3 = std::move(cb1);
  std::cout << "test" << std::endl;
  SafeCallback<> cb2 = cb1;
  SafeCallback<> cb4 = std::move(cb3);
  cb1 = cb2;
  SafeCallback<>& cb5 = cb1;
  cb2 = foo;
  std::swap(cb1, cb2);
}