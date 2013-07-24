#include <functional>
#include <map>
#include <tuple>
#include <utility>

/*! \brief A template functor class that can be utilized to memoize any 
*          given function taking any number of arguments. 
*/
template <typename R, typename... Args>
struct memoize_wrapper
{
private:

    std::map<std::tuple<Args...>, R> memo_;
    std::function<R(Args...)> func_;

public:

    /*! \brief Auto memoization constructor.
     *  
     *  \param func an the std::function to be memoized.
    */
    memoize_wrapper(std::function<R(Args...)> func)
      : func_(func)
    { }

    /*! \brief Memoization functor implementation.
     *  
     *  \param a Argument values that match the argument types for the 
     *           (previously) supplied function. 
     *  \return A value of return type R equivalent to calling func(a...).
     *          If this function has been called with these parameters
     *          previously, this will take O(log n) time.
    */
    R operator()(Args&&... a)
    {
        auto tup = std::make_tuple(std::forward<Args>(a)...);
        auto it = memo_.find(tup);
        if(it != memo_.end()) {
            return it->second;
        }
        R val = func_(a...);
        memo_.insert(std::make_pair(std::move(tup), val));
        return val;
    }

}; //end struct memoize_wrapper

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

long factorial(long i)
{
    std::cout << "factorial(" << i << ")\n";
    if(i == 0) return 1;
    else return i * factorial(i-1);
}

int main()
{
    std::vector<int> arg {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::transform(arg.begin(), arg.end(), arg.begin(), memoize_wrapper<long, long>(factorial));
    for(long i : arg) {
        std::cout << i << "\n";
    }
}