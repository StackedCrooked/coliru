#include <iostream>

struct foo
{
    void bar(int i) 
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << i << '\n';
    }
};

void func(void(*p)(void *, int i), void *userdata)
{
    (*p)(userdata, 42);
}

int main()
{
    foo f;
    func([](void *userdata, int i) {
            static_cast<foo *>(userdata)->foo::bar(i);
        }, &f);
}
