struct Foo {
    enum class Bar { one, two };
    
    Foo(Bar b) : bar(b) { }
    
};

int main()
{
    Foo x;
    return 0;
}