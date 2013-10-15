template<class T>
class templ;

template<class T>
void foo()
{
    templ<T> nc;
    nc.m = 42;
    
    templ<const T> c;
    c.m = 42;
}

template<class T>
class templ
{
    friend void foo<T>();
    int m;
};

int main()
{
    foo<int>();
}
