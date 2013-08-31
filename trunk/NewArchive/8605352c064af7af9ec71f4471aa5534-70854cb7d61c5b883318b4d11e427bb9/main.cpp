#include <thread>
#include <future>

template<typename T>
struct X
{
    X() : t() { }

    X(X&& x) : X(std::unique_lock<std::mutex>(x.m), std::move(x)) { }

    X(std::unique_lock<std::mutex> const& l, X&& x) : X(std::move(x))
    {
    }

private:
    std::mutex m;
    T t;
};

int main()
{
}