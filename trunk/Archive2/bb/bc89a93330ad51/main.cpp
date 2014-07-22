#include <functional>
#include <iostream>

struct Base {
    using callback_t = std::function<void()>;

    void async_call(callback_t cb = callback_t{}) {
        if (cb)
            def_cb = cb;
        def_cb();
    }
    
    void def_callback() {
        do_callback();
    }

protected:
    virtual void do_callback() {
        std::cout << "default. user may override.\n";
    }

private:
    callback_t def_cb = std::bind(&Base::def_callback, this);        
};

struct User : Base {
    virtual void do_callback() override {
        std::cout << "Hello World!\n";
    }
};

int main() {
    Base b;
    User u;

    b.async_call(); // default
    u.async_call(); // user extension
    u.async_call([](){std::cout << "I want this now!\n";}); // set and usenew callback
}
