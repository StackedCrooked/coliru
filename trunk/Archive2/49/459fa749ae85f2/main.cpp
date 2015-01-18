#include <functional>
#include <memory>
#include <vector>
#include <future>

template <typename F, typename... Args>
typename std::result_of<F(Args...)>::type pushTask(F&& f, Args&&... args)
{
    using result_type = typename std::result_of<F(Args...)>::type;

    // create a functional object of the passed function with the signature std::function<result_type(void)> by creating a
    // bound Functor lambda which will bind the arguments to the function call through perfect forwarding and lambda capture
    auto boundFunctor = [func = std::move(std::forward<F>(f)),
                         argsTuple = std::move(std::make_tuple(std::forward<Args>(args)...))](void) mutable->result_type
    {
        // forward function and turn variadic arguments into a tuple
        return result_type();
    };

    // create a packaged task of the function object
    //std::function<result_type(void)> taskFunctor{ std::move(boundFunctor) };
      std::packaged_task<result_type(void)> taskFunctor{ std::move(boundFunctor) };
}

 int main(int argc, char *argv [])
 {
     auto testvup = [](std::vector<std::unique_ptr<int>>&& vup)
    {

    };
    std::vector<std::unique_ptr<int>> vup;
    pushTask(testvup, std::move(vup));
}