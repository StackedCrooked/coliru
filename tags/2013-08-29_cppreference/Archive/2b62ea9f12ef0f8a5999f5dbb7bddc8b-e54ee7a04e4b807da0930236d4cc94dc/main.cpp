#include <future>
#include <iostream>


template<typename F>
auto defer(F&& f) -> std::future<decltype(f())>
{
    return std::async(std::launch::deferred, std::forward<F>(f));
}

template<typename T>
auto make_ready_future(T&& t = T{}) -> std::future<T>
{
    struct fun
    {
        fun(T&& t) : t(std::move(t)) {}
        
        T operator()()
        {
            return std::move(t);
        }
        
        T t;
    };
    return defer(fun(std::move(t)));
}


struct Movable
{
    Movable() = default;
    Movable(Movable&&) = default;
    Movable& operator=(Movable&&) = default;
    Movable(const Movable&) = delete;
    Movable& operator=(const Movable&) = delete;
};


std::ostream& operator<<(std::ostream& os, const Movable& m)
{
    return os << "Movable";
}

int main()
{
    defer([]{std::cout << "Deferred." << std::endl;});
    
    
    std::future<int> f = make_ready_future<int>();
    std::cout << f.get() << std::endl;
    
    std::future<Movable> m = make_ready_future<Movable>();
    std::cout << m.get() << std::endl;
}