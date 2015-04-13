#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <map>

class CallBackManager {

  public:
    typedef boost::function<void()>         DisplaySig;
    typedef boost::function<void(int, int)> MouseSig;
    typedef boost::variant<DisplaySig, MouseSig> AnySig;

    enum CallBackType { DISPLAY = 1 << 0, MOUSE = 1 << 1 };
    struct display_callback_t;

    void AddCallback(CallBackType type, int hwnd, AnySig f) {
        using boost::get;
        switch(type) {
            case DISPLAY: return addDisplayCallback(hwnd, get<DisplaySig>(f));
            case MOUSE:   return addMouseCallback(hwnd, get<MouseSig>(f));
            default: throw std::runtime_error("Unsupported CallBackType");
        }
    }

    void test() {
        for (auto& f : _display_callback)
            boost::get<DisplaySig>(f.second)();
        for (auto& f : _mouse_callback)
            boost::get<MouseSig>(f.second)(rand(), rand());
    }
  private:
    void addDisplayCallback(int hwnd, DisplaySig f) { _display_callback.emplace(hwnd, f); }
    void addMouseCallback(int   hwnd, MouseSig f)   { _mouse_callback.emplace(hwnd, f); }

    std::map<int, AnySig> _display_callback, _mouse_callback;
};

#include <iostream>
struct Foo {

    int my_handle;
    CallBackManager cbm;

    Foo()
    {
        cbm.AddCallback(CallBackManager::DISPLAY, my_handle, 
                CallBackManager::DisplaySig(boost::bind(&Foo::Display, this)));

        cbm.AddCallback(CallBackManager::MOUSE, my_handle, 
                CallBackManager::MouseSig(boost::bind(&Foo::Mouse, this, _1, _2)));
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
