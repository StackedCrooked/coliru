#include <thread>

class Foo {
public:
    ~Foo() {
        if (_th.joinable())
            _th.join();
    }
    void threadFunc() {}
    void startThread() {
        _th = std::thread(&Foo::threadFunc, std::ref(*this));
    }
private:
    std::thread _th;
};

int main()
{
    Foo f;
    f.startThread();
}
