struct Foo
{
    void m() {}
};

template<typename C, void (C::*f)()>
void bar(C* obj)
{
    (obj->*f)();
}

int main() 
{
    Foo foo;
    bar<Foo, &Foo::m>(&foo);
}