#include <iostream>
#include <functional>
#include <future>
#include <thread>

class test
{
    int fthread(int b)
    {
        return a + b;
    }

    int a;
public:
    test(int a_) : a(a_) {}

    int run(int b)
    {
        std::packaged_task<int(int)>
                task(std::bind(&test::fthread, this, std::placeholders::_1));
        std::future<int> fut = task.get_future();

        std::thread(std::ref(task), b).join();

        return fut.get();
    }

    int run2(int b)
    {
        return std::async(std::launch::async, [this,b]{ return fthread(b); }).get();
    }
};

int main()
{
    int a = 5, b = 1;
    test t(a);

    int c = t.run(b);

    std::cout << std::boolalpha << (c == a + b) << '\n';
    std::cout << (a + b == t.run2(b)) << '\n';
}
