#include <memory>
#include <functional>
#include <iostream>

struct concrete_deleter
{
    template<typename T> concrete_deleter(T*) : del_(&delete_it<T>) {}

    void operator()(void* ptr) const
    {
        (*del_)(ptr);
    }
  private:
    using del_t = void(*)(void*);
    del_t del_;

    template <typename T> static void delete_it(void *p) { delete static_cast<T*>(p); }
};

template<typename T>
using Ptr = std::unique_ptr<T, concrete_deleter>;

template<typename T, typename... Args>
std::unique_ptr<T, concrete_deleter> make_unique_poly(Args&&... args)
{
   return std::unique_ptr<T, concrete_deleter>{new T{std::forward<Args>(args)...}, static_cast<T*>(nullptr)};
}

struct Base           { ~Base()    { std::cout << __PRETTY_FUNCTION__ << "\n"; } };
struct Derived : Base { ~Derived() { std::cout << __PRETTY_FUNCTION__ << "\n"; } };

int main()
{
    Ptr<Derived> d = make_unique_poly<Derived>();
    Ptr<Base>    b = make_unique_poly<Base>();
    b = std::move(d);
    std::cout << "Bye bye\n";
}
