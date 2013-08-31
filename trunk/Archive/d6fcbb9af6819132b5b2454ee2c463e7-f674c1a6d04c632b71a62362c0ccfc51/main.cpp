
void real_foo(int&)
{
}


template<typename T>
void foo(T t)
{
    real_foo(t);
}


int main()
{
    foo(int());    
    foo(short());
}