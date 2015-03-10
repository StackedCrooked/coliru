#include <functional>
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
        if ((*is_valid_) == true)
        {
            callback_(std::forward<Arg>(parameters)...);
        }
    }
 
private:
    std::shared_ptr<bool> is_valid_;
    FunctionType callback_;
};
 
template<typename T>
SafeCallback<decltype(T::operator())>
makeSafe(std::shared_ptr<bool> is_valid, T callback)
{
    return SafeCallback<decltype(T::operator())>(is_valid, callback);
}
 
int main()
{
    std::shared_ptr<bool> guard;
	makeSafe(guard, [] (int value) { /* Do sthing */ });
}
 