#include <functional>   // for std::bind
#include <memory>       // for std::unique_ptr
#include <utility>      // for std::move
#include <future>       // for std::packaged_task
#include <iostream>     // printing
#include <type_traits>  // for std::result_of
#include <cstddef>

void showPtr(const char* name, const std::unique_ptr<size_t>& ptr)
{
    std::cout << "- &" << name << " = " << &ptr << ", " << name << ".get() = "
              << ptr.get();
    if (ptr)
        std::cout << ", *" << name << " = " << *ptr;
    std::cout << std::endl;
}

// If you must use std::function, but your function is MoveConstructable
// but not CopyConstructable, you can wrap it in a shared pointer.
template <typename F>
class shared_function : public std::shared_ptr<F> {
public:
    using std::shared_ptr<F>::shared_ptr;

    template <typename ...Args>
    auto operator()(Args&&...args) const
        -> typename std::result_of<F(Args...)>::type
    {
        return (*(this->get()))(std::forward<Args>(args)...);
    }
};

template <typename F>
shared_function<F> make_shared_fn(F&& f)
{
    return shared_function<F>{
        new typename std::remove_reference<F>::type{std::forward<F>(f)}};
}


int main()
{
    std::unique_ptr<size_t> myPointer(new size_t{42});
    showPtr("myPointer", myPointer);
    std::cout << "Creating lambda\n";

#if __cplusplus == 201103L // C++ 11

    // Use std::bind
    auto lambda = std::bind([](std::unique_ptr<size_t>& myPointerArg){
        showPtr("myPointerArg", myPointerArg);  
        *myPointerArg *= 56;                    // Reads our movable thing
        showPtr("myPointerArg", myPointerArg);
        myPointerArg.reset(new size_t{*myPointerArg * 237}); // Writes it
        showPtr("myPointerArg", myPointerArg);
    }, std::move(myPointer));

#elif __cplusplus > 201103L // C++14

    // Use generalized capture
    auto lambda = [myPointerCapture = std::move(myPointer)]() mutable {
        showPtr("myPointerCapture", myPointerCapture);
        *myPointerCapture *= 56;
        showPtr("myPointerCapture", myPointerCapture);
        myPointerCapture.reset(new size_t{*myPointerCapture * 237});
        showPtr("myPointerCapture", myPointerCapture);
    };

#else
    #error We need C++11
#endif

    showPtr("myPointer", myPointer);
    std::cout << "#1: lambda()\n";
    lambda();
    std::cout << "#2: lambda()\n";
    lambda();
    std::cout << "#3: lambda()\n";
    lambda();

#if ONLY_NEED_TO_CALL_ONCE
    // In some situations, std::packaged_task is an alternative to
    // std::function, e.g., if you only plan to call it once.  Otherwise
    // you need to write your own wrapper to handle move-only function.
    std::cout << "Moving to std::packaged_task\n";
    std::packaged_task<void()> f{std::move(lambda)};
    std::cout << "#4: f()\n";
    f();
#else
    // Otherwise, we need to turn our move-only function into one that can
    // be copied freely.  There is no guarantee that it'll only be copied
    // once, so we resort to using a shared pointer.
    std::cout << "Moving to std::function\n";
    std::function<void()> f{make_shared_fn(std::move(lambda))};
    std::cout << "#4: f()\n";
    f();
    std::cout << "#5: f()\n";
    f();
    std::cout << "#6: f()\n";
    f();
#endif
}
