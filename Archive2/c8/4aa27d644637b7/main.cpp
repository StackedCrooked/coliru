#include <iostream>
#include <utility>
#include <functional>
#include <string>

template <typename F>
class Rail
{
public:
    Rail(F f)
      : f_(f)
    {
    }
    
    template <typename T>
    decltype(std::declval<F>()(std::declval<T>())) operator()(T t)
    {
        return f_(t);
    }
    
    template <typename F2>
    Rail<decltype(std::bind(std::declval<F2>(), std::bind(std::declval<F>(), std::placeholders::_1)))>
    operator>>(F2&& f)
    {
        return Rail<decltype(std::bind(std::declval<F2>(), std::bind(std::declval<F>(), std::placeholders::_1)))>
                (std::bind(f, std::bind(f_, std::placeholders::_1)));
    }
    
private:
    F f_;
};

template <typename F>
Rail<decltype(std::bind(std::declval<F>(), std::placeholders::_1))> make_rail(F&& f)
{
    return Rail<decltype(std::bind(f, std::placeholders::_1))>(std::bind(f, std::placeholders::_1));
}

int square(int i)
{
    return i * i;
}

std::string to_string(int i)
{
    return std::to_string(i);
}

std::string double_string(std::string s)
{
    return s + s;
}

int main()
{
    auto f = make_rail(square) >> to_string >> double_string;
    std::cout << f(2) << std::endl;
  
    return 0;
}