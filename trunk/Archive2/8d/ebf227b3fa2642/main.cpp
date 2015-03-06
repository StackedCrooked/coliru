#include <utility>
#include <memory>

template<typename R, typename... Args>
struct holder_base {
    virtual ~holder_base() = default;
    
    virtual std::unique_ptr<holder_base> clone() const = 0;
    virtual R call(Args... args) = 0;
};

template<typename Functor, typename R, typename... Args>
struct holder: holder_base<R, Args...> {
    explicit holder(Functor functor): functor(std::move(functor)) {}
    
private:
    Functor functor;

public:
    R call(Args... args) override { return functor(std::forward<Args>(args)...); }
    std::unique_ptr<holder_base<R, Args...>> clone() const override
    { return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename Functor, typename... Args>
struct holder<Functor, void, Args...>: holder_base<void, Args...> {
    explicit holder(Functor functor): functor(std::move(functor)) {}
    
private:
    Functor functor;

public:
    void call(Args... args) override { functor(std::forward<Args>(args)...); }
    std::unique_ptr<holder_base<void, Args...>> clone() const override
    { return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename R, typename... Args>
struct function {
    template<typename Functor>
    function(Functor functor): functor(new holder<Functor, R, Args...>(std::move(functor))) {}
    
    function(function const& other): functor(other.functor.clone()) {}
    function& operator=(function const& other) { functor = other.functor.clone(); return *this; }
    
    function(function&&) = default;
    function& operator=(function&&) = default;
    
    R operator()(Args... args) { return functor->call(std::forward<Args>(args)...); }
private:
    std::unique_ptr<holder_base<R, Args...>> functor;
};


// function<int, int> f;
//function<int, int> f();
function<int, int> f = [&](int j) { return 0; };

int main()
{
    int i = 0;
    f = [&i](int j) { return i+j; };
    int r1 = f(3);
    f = [&i](int j) { return 2*(i+j); };
    int r2 = f(3);
    return r1+r2;
}