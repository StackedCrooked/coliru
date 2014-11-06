#include <iostream>




template<typename Signature>
struct Function;


template<typename R, typename ...Params>
struct Function<R(Params...)>
{
    template<R(*function_address)(Params...)>
    struct FromAddress
    {
        template<typename ...Args>
        R operator()(Args&& ...args)
        {
            return function_address(std::forward<Args>(args)...);
        }
    };
};



int increment(int n) { return n + 1; }


int main()
{
    auto inc = Function<int(int)>::FromAddress<increment>();
    std::cout << inc(3) << std::endl;
    std::cout << inc(1.0) << std::endl;
    
}
