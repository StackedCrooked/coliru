#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <map>

class CallBackManager {

  public:
    enum CallBackType { DISPLAY = 1 << 0, MOUSE = 1 << 1 };
    struct display_callback_t;

    template <typename F>
    void AddDisplayCallback(int hwnd, F f) {
        addDisplayCallback(hwnd, f);
    }

    template <typename F>
    void AddMouseCallback(int hwnd, F f) {
        addMouseCallback(hwnd, f);
    }

    void test() {
        for (auto& f : _display_callback)
            f.second();
        for (auto& f : _mouse_callback)
            f.second(rand(), rand());
    }
  private:
    void addDisplayCallback(int hwnd, boost::function<void()> f) { _display_callback[hwnd] = f; };

    void addMouseCallback(int hwnd, boost::function<void(int, int)> f) { _mouse_callback[hwnd] = f; };

    std::map<int, boost::function<void()>> _display_callback;
    std::map<int, boost::function<void(int, int)>> _mouse_callback;
};

#include <iostream>
struct Foo {

    int my_handle;
    CallBackManager cbm;

    Foo()
    {
        cbm.AddDisplayCallback(my_handle, boost::bind(&Foo::Display, this));
        cbm.AddMouseCallback(my_handle, boost::bind(&Foo::Mouse, this, _1, _2));
    }

    void Mouse(int, int) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
    void Display() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
};

int main() {
    Foo instance;
    instance.cbm.test();
}
