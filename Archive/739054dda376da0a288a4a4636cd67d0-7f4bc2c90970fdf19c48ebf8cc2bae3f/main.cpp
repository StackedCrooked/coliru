#include <thread>

class Foo
{
public:
    template <class T, class U>
    void func()
    {

    }
};

int main()
{
    Foo f;
    std::thread t(&Foo::func<int, int>, &f);
    t.join();
    return 0;
}
