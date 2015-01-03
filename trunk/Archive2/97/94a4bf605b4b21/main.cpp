#include <thread>

class interruptible
{
public:
    template <typename F, typename... A>
    interruptible(F&& Function, A&&... Arguments) :
        Thread(
            [](F&& Function, A&&... Arguments)
            {
                Function(std::forward<A>(Arguments)...);
            },
            std::forward<F>(Function),
            std::forward<A>(Arguments)...
        )
    { }

private:
    std::thread         Thread;
};

void DoStuff()
{
}


int main()
{
    interruptible a(DoStuff);

    return 0;
}