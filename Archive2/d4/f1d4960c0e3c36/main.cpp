#include <iostream>
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
struct UniquePtr
{
    explicit UniquePtr(T* t): ptr(t) {}
    ~UniquePtr() { Deleter()(ptr); }

    T& operator*() { return *ptr; }
    const T& operator*() const { return *static_cast<T const*>(ptr); }

    T* operator->() { return ptr; }
    T const* operator->() const { return static_cast<T const*>(ptr); }

private:
    T* ptr;
};

struct Foo
{
    Foo(): x(0) {}
    ~Foo() { std::cout << "deleting Foo" << std::endl; }

    void Bar() { x++; }
    void Baz() const { std::cout << x << std::endl; }

private:
    int x;
};

int main()
{
    UniquePtr<Foo> p1(new Foo());
    (*p1).Baz();
    (*p1).Bar();
    p1->Baz();
    p1->Bar();

    const UniquePtr<Foo> p2(new Foo());
    (*p2).Baz();
    (*p2).Bar();
    p2->Baz();
    p2->Bar();

    return 0;
}