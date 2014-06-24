#include <future>


class WorkQue
{
    public:
        template<typename Func, typename ...Args>
        auto addItem(Func && task, Args... args) -> std::future<decltype(task(args...))>
        {
            using R = decltype(task(args...));
            std::promise<R>     promise;
            std::future<R>      future = promise.get_future();

            // STUFF

            return future;
        }
};

int main()
{
    WorkQue     que;
    int         x = 1;
    int         y = 2;

    // This fails
    que.addItem([](int x, int y){return x+y;}, x, y);

    // I can see needing to specify the return type.
    // But even this does not work.
    // que.addItem<int>([](int x, int y){return x+y;}, x, y);

    // This works fine.
    // But I was hoping not to need to specify this every time.
    //que.addItem<int>(std::function<int(int,int)>([](int x, int y){return x+y;}), x, y);
}