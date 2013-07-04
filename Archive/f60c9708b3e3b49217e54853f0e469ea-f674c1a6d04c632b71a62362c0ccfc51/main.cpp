#include <iostream>
#include <thread>
#include <vector>

class foo
{
public:
    void make_foo_func_threads()
    {
        for (int i = 0; i < 5; ++i)
            some_threads.push_back(std::thread(&foo::foo_func, this));
        for (auto& t: some_threads) t.join();
    }

private:
    void foo_func() { std::cout << "Hello\n"; }
    std::vector<std::thread> some_threads;
};

int main()
{
    foo f;
    f.make_foo_func_threads();
}
