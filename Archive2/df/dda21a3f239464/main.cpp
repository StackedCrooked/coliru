template<int i>
struct base
{
    void purr() {}
};

int purr() { return 42; }

template<class T>
struct foo : T
{
    void meow()
    {
        T t;
        t.base < 0 > ::purr();
    }
};

struct T0 : base<0> {};
struct T1 { int base; };

int main()
{
    foo<T0>().meow();
    //foo<T1>().meow();
}