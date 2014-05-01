#include <type_traits>
#include <memory>
#include <functional>

template<class R>
struct Wrapper {
    template<typename T, typename F>
    R operator()(std::weak_ptr<T>& obj, F&& func)
    {
        auto ptr = obj.lock();
        if (ptr)
            return func();
    }
    template<typename T, typename F, class R2>
    R operator()(std::weak_ptr<T>& obj, F&& func, R2&& ret)
    {
        auto ptr = obj.lock();
        if (ptr) 
            return func();
        else    
            return std::forward<R2>(ret);
    }
};

struct Bind {
    
    // void return
    template<typename F, typename T, typename... A>
    static auto Weak(F&& func, const std::shared_ptr<T>& obj, A&&... args)
      -> typename std::enable_if<std::is_same<decltype(func(obj.get(),std::forward<A>(args)...)),void>::value, std::function<void()>>::type
    {return std::bind(Wrapper<void>(), std::weak_ptr<T>(obj), std::function<void()>(std::bind(func, obj.get(),std::forward<A>(args)...)));}
    
    // nonvoid return
    template<typename RP, typename F, typename T, typename... A>
    static auto Weak(RP&& ret, F&& func, const std::shared_ptr<T>& obj, A&&... args)
      ->std::function<decltype(true?ret:func(obj.get(),std::forward<A>(args)...))()>
    {
        using RR = decltype(true?ret:func(obj.get(),std::forward<A>(args)...));
        return std::bind(Wrapper<RR>(), std::weak_ptr<T>(obj), std::function<RR()>(std::bind(func, obj.get(), std::forward<A>(args)...)), std::forward<RP>(ret));
    }

};


#include <iostream>
int main() {
    std::shared_ptr<int> obj;
    
    
    auto one = Bind::Weak([](int*, int)->void{}, obj, 3);
    auto two = Bind::Weak(true, [](int*, char)->bool {return false;}, obj, '7');
    auto three = Bind::Weak(42, [](int*, const char*)->int{return 3;}, obj, "HI");
    
    one();
    bool a = two();
    int b = three();
    std::cout << a << b;
}