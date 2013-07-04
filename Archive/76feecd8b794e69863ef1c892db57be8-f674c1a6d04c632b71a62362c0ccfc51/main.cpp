
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
    foo(n); // ok
    
    short s;
    foo(s); // error
}