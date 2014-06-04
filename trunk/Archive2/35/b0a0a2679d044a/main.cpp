#include <iostream>
#include <cstddef>
#include <utility>


// Alternative to std::function that uses avoids heap allocation
// and uses static storage instead (with an upper bound then).


template<typename Signature>
struct Function;


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    template<typename F>
    Function(F&& f)
    {
        // we must not exceed static storage
        static_assert(sizeof(f) <= sizeof(mStorage), "");
        
        // use placement new to create the derived Func<T> inside the storage
        new (&mStorage) Func<F>(std::forward<F>(f));
        
    }
    
    R operator()(Args&& ...args) const
    {
        // up-cast Storage to Base
        const Base& base = mStorage;
        
        // down-cast Base to FuncBase
        auto& funcBase = static_cast<const FuncBase&>(base);
        
        // call virtual method
        return funcBase(std::forward<Args>(args)...);
    }    
    
private:
    struct Base
    {
    };
    
    struct Storage : Base
    {
        // Crash:
        std::aligned_storage<32, 32>::type mStorage;
        
        // OK
        // alignas(32) char mStorage[32];
    };
    
    struct FuncBase : Base
    {
        virtual R operator()(Args&& ...args) const = 0;
    };
    
    template<typename F>
    struct Func : FuncBase
    {
        Func(F&& f) : f(std::forward<F>(f))
        {
        }
        
        virtual R operator()(Args&& ...args) const override final
        {
            return f(std::forward<Args>(args)...);
        }
        
        F f;
    };
    
    Storage mStorage;
};


int main()
{
    Function<int(int, int)> sum = [](int a, int b) {
        return a + b;
    };
    
    Function<int()> sum_2_4 = [sum]{
        return sum(2, 4);
    };
    
    std::cout << sum_2_4() << std::endl;
}

