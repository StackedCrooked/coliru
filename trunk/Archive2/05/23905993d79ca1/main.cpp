#include <functional>
#include <iostream>

template<class... Args>
class SafeCallback
{
public:
    SafeCallback()
    {
    }
    
    template <typename T>
    SafeCallback(T&& f)
    : _f(std::forward<T>(f))
    {
    }
    
    template <typename T>
    SafeCallback& operator=(T&& f)
    {
        _f = std::forward<T>(f);
        return *this;
    }

    void operator()(Args&& ...args)
    {
        if (_f)
        {
            _f(std::forward<Args>(args)...);
        }
    }
    
    operator bool() const
    {
        return (bool)_f;
    }
    
private:
    std::function<void(Args...)> _f;
};

int main()
{
    SafeCallback<int, int> cb1 = [](int i, int j) { std::cout << i << "+" << j << "=" << (i+j) << std::endl;  };
    SafeCallback<int, int> cb2 = [](int i, int j) { std::cout << i << "+" << j << "=" << (i-j) << std::endl;  };
    
    cb1 = cb2;

    return 0;
}