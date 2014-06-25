#include <future>
#include <iostream>
#include <utility>

class WorkQue
{
    public:
        template<typename Func, typename ...Args>
        auto addItem(Func && task, Args &&... args) -> std::future<decltype(task(std::forward<Args>(args)...))>
        {
            using R = decltype(task(std::forward<Args>(args)...));
            std::promise<R>     promise;
            std::future<R>      future = promise.get_future();

            // STUFF

            return future;
        }
};

class PerfectWorkQue
{
    public:
        template<typename Func, typename ...Args>
        auto addItem(Func && task, Args &&... args) -> std::future<decltype(std::forward<Func>(task)(std::forward<Args>(args)...))>
        {
            using R = decltype(std::forward<Func>(task)(std::forward<Args>(args)...));
            std::promise<R>     promise;
            std::future<R>      future = promise.get_future();

            // STUFF

            return future;
        }
};

struct A{};
struct B{};

struct MyFunc {
    A operator()() const & {
        return {};
    }
    B operator()() const && {
        return {};
    }
};

int main()
{
    MyFunc lvalue;
    WorkQue     que;
    int         x = 1;
    int         y = 2;

    que.addItem([](int x, int y){return x+y;}, x, y);
    std::future<A> futureA1{que.addItem(lvalue)};
    //std::future<B> futureB1{que.addItem(MyFunc{})}; //Doesn't compile
    
    PerfectWorkQue perfectQue;
    
    std::future<A> futureA2{perfectQue.addItem(lvalue)};
    std::future<B> futureB2{perfectQue.addItem(MyFunc{})};

}