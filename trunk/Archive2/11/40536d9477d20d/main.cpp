#include <tuple>
#include <utility>
#include <cstddef>
#include <iostream>
#include <utility>

template<typename R>
class Wrapper
{
public:
    Wrapper(R r)
    : m_r(r)
    {
    }
    R get() const
    {
        return m_r;
    }
private:
    R m_r; 
};

template<typename T>
class Wrapper<T&&>
{
public:
    Wrapper(T&& r)
    : m_r(std::move(r))
    {
    }
    //T& get() const
    //{
        //return m_r;
    //}
private:
    T& m_r; 
};

template<typename T>
auto wrap(T&&x) -> Wrapper<decltype((x))>
{
    return {x};
}

int main()
{
    std::cout << wrap(std::string("sdsfsd")).get() << std::endl;
    
    auto y = wrap(std::string("sdsfsd"));
    std::cout << y.get() << std::endl;
    y.flibble();
  
  return 0;
}

