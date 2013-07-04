
void real_foo(int&)
{
}


template<typename T>
void foo(T& t)
{
    real_foo(t);
}


int main()
{
    int n;
    foo(n);
    
    short s;
    foo(s);
}