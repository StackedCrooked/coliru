#include <iostream>
#include <functional>
#include <utility>


template<typename T>
struct Lazy
{
    // construct with "factory" functor
    template<typename F>
    Lazy(F&& f) : func(std::forward<F>(f)) { }
    
    // returns (or creates) the object
    T* operator->()
    {
        std::cout << "get or create the Example: ";
    
        // call the functor to get the result
        T* ptr = func();
        
        // modify the functor to always return the precalculated result
        func = [ptr]() {
            std::cout << "return cached result\n";
            return ptr;
        };
        
        // return the result
        return ptr;
    }
    
private:
    std::function<T*()> func; 
};



int main()
{
    struct Example
    {
        Example() { std::cout << "create Example\n"; }
        
        Example(const Example&) = delete;
        Example& operator=(const Example&) = delete;
        
        void test() {  }
    };
    
    Lazy<Example> example([]{ return new Example; }); // it's a leaky abstraction ;)
    example->test();
    example->test();
    example->test();
}
