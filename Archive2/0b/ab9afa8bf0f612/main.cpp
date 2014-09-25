#include <future>
#include <cassert>
#include <iostream>


template<typename T>
struct Future
{
    Future(std::future<T>&& inFuture) : mFuture(std::move(inFuture)) {}

    Future(Future&&) noexcept = default;
    Future& operator=(Future&&) noexcept = default;

    Future(const Future&) noexcept = delete;
    Future& operator=(const Future&) noexcept = delete;

    ~Future() = default;

    template<typename F>
    auto then(F&& f) -> Future<decltype(f(std::declval<T>()))>
    {
        return std::async(std::launch::deferred, [=](F f) {
            return f(mFuture.get());
        }, std::forward<F>(f));
    }

    template<typename F>
    void finally(F&& f)
    {
        f(mFuture.get());
    }

    template<typename F>
    auto operator+(F&& f) -> Future<decltype(f(std::declval<T>()))>
    {
        return then(std::forward<F>(f));
    }

    template<typename F>
    void operator=(F&& f)
    {
        f(mFuture.get());
    }

    template<typename F>
    auto operator()(F&& f) -> decltype(then(std::forward<F>(f)))
    {
        return then(std::forward<F>(f));
    }

    T operator()()
    {
        return get();
    }

    T get()
    {
        return mFuture.get();
    }

    std::future<T> mFuture;
};


template<typename F>
auto Launch(F&& f) -> Future<decltype(f())>
{
    return Future<decltype(f())>(std::async(std::launch::deferred, std::forward<F>(f)));
}


auto Launch() -> Future<void>
{
    return Future<void>(std::async(std::launch::deferred, []{}));
}


template<typename T>
auto MakeReadyFuture(T t) -> Future<T>
{
    return std::async(std::launch::deferred, [](T t){ return t; }, std::move(t));
}

int main()
{
    Launch([]{
        return 1;
    }).then([](int n) {
        std::cout << n << ' ';
        return n + 1;
    }).then([](int n) {
        std::cout << n << ' ';
        return n + 1;
    }).then([](int n) {
        std::cout << n << ' ';
        return n + 1;
    }).finally([](int n){
        std::cout << n << '\n';
    });


    MakeReadyFuture(2)
        + [](int n) { std::cout << n << ' '; return 3 * n / 2; }
        + [](int n) { std::cout << n << ' '; return 3 * n / 2; }
        + [](int n) { std::cout << n << ' '; return 3 * n / 2; }
        = [](int n) { std::cout << n << "\n"; };
        
        
    std::cout << "end of program";

}
