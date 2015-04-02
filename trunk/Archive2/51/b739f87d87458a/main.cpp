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
        std::cout << "construction" << std::endl;
    }

    void operator()(Args&& ...args)
    {
        if (_f)
        {
            _f(std::forward<Args>(args)...);
        }
        else
        {
            std::cout << "empty" << std::endl;
        }
    }
    
    template <class T>
    SafeCallback& operator=(const T& t)
    {
        std::cout << "assign" << std::endl;
        _f = t;
        return *this;
    }
    
    operator bool() const
    {
        return _f;
    }
    
private:
    std::function<void(Args...)> _f;
};

int main()
{
    SafeCallback<int, int> cb1 = [](int i, int j) { std::cout << i << "+" << j << "=" << (i+j) << std::endl;  };
    SafeCallback<int, int> cb2 = [](int i, int j) { std::cout << i << "+" << j << "=" << (i-j) << std::endl;  };

    cb1(1, 2);
    cb2(1, 2);
    
    cb1 = cb2;
    
    cb1 = nullptr;
    cb1 = [](int, int) { std::cout << "new" << std::endl;  };
    
    cb1(3, 4);
    cb2(3, 4);

    return 0;
}