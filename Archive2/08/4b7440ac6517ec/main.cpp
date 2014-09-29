void fail();
void eat_all(...);
bool get_bool();

struct Foo {
    int a, b, c;
    Foo();
    
    Foo(Foo&&);
    Foo& operator=(Foo&&);
    
    Foo(const Foo&) { fail(); }
    Foo& operator=(const Foo&) { fail(); return *this; }
};

Foo test() {
    Foo x, y;

    eat_all(&x, &y); // force creation of both x and y

    if (get_bool())
        return x;
        
    return y;
}