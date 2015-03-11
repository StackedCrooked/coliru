#include <functional>
#include <iostream>
#include <memory>
 
template<typename T>
class SafeCallback
{
public:
    typedef std::function<T> FunctionType;
    SafeCallback(std::shared_ptr<bool> is_valid, FunctionType callback)
        : is_valid_(is_valid), callback_(callback)
    {
    }
 
    template <class ...Arg>
    void operator()(Arg&&... parameters)
    {
        //if ((*is_valid_) == true)
        {
            callback_(std::forward<Arg>(parameters)...);
        }
    }
 
private:
    std::shared_ptr<bool> is_valid_;
    FunctionType callback_;
};

template <typename T> struct helper : helper<decltype(&T::operator())> {};

template <typename Ret, typename C, typename ... Args>
struct helper<Ret (C::*)(Args...) const>
{
    using type = Ret(Args...);
};

template<typename T>
SafeCallback<typename helper<T>::type>
makeSafe(std::shared_ptr<bool> is_valid, T callback)
{
    return SafeCallback<typename helper<T>::type>(is_valid, callback);
}
 
int main()
{
    std::shared_ptr<bool> guard;
	auto safe = makeSafe(guard, [] (int value) { std::cout << value << std::endl; });
    safe(42);
}