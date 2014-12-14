#include <iostream>
#include <functional>

template<typename T>
struct Foo
{
    Foo(T sum) : sum_(sum) {};
    Foo<T> method_one(const Foo<T>& foo) const { Foo<T> res(sum_ + foo.sum_); return res; }
    Foo<T> method_two(const Foo<T>& foo) const { Foo<T> res(sum_ + foo.sum_ + 10); return res; }
    Foo<T> method_three(const Foo<T>& foo, T val) const { Foo<T> res(sum_ + foo.sum_ + val); return res;}
    friend std::ostream &operator << (std::ostream & output, const Foo &foo) { output << foo.sum_; return output;}

    T sum_;
};

template<typename T>
void do_the_work(const Foo<T>& a, const Foo<T>& b, std::function<Foo<T>(const Foo<T>&, const Foo<T>&)> func)
{
    // I do stuff before [...]
    Foo<T> c = func(a, b);
    std::cout << c << std::endl;
    // I do stuff after [...]
}

int main()
{
    Foo<float> a(1.0);
    Foo<float> b(2.0);


    // I would like to replace this
    Foo<float> c = a.method_two(b);
    std::cout << c;  // 1 + 2 + 10

    std::function<Foo<float>(const Foo<float>&, const Foo<float>&)> f = &Foo<float>::method_one;
    // with something like that
    do_the_work<float>(a, b, &Foo<float>::method_one);
    do_the_work<float>(a, b, &Foo<float>::method_two);
}