#include <utility>
#include <iostream>
#include <memory>

struct base {
    ~base() { std::cout << "base\n"; }
};

struct derived:base {
    ~derived() { std::cout << "derived\n"; }
};

    struct deleter {
      void* state;
      void(*f)(void*);
      void operator()(void*)const{if (f) f(state);}
      deleter(deleter const&)=default;
      deleter(deleter&&o):deleter(o) { o.state = nullptr; o.f=nullptr; }
      deleter()=delete;
      template<class T>
      deleter(T*t):
        state(t),
        f([](void*p){delete static_cast<T*>(p);})
      {}
    };
    template<class T>
    using smart_unique_ptr = std::unique_ptr<T, deleter>;

    template<class T, class...Args>
    smart_unique_ptr<T> make_smart_unique( Args&&... args ) {
      T* t = new T(std::forward<Args>(args)...);
      return { t, t };
    }

int main() {
    smart_unique_ptr<base> ptr = make_smart_unique<derived>();
    ptr.reset();
}