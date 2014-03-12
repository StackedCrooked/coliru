struct abstract
{
    virtual void foo() = 0;
};

template<class X, class Y>
struct templ {};

template<class T>
struct bar
{
    template<class U>
    bar(templ<U[], T[]>) {}
};

int main()
{
    bar<abstract> x;
}