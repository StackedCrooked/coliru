class Foo {
    // here, compiler doesn't yet know what Bar is
    union Bar {
        int iBar;
        double rBar;
        bool bBar;
    } bar; // now it does
public:
    static Bar getBar(Foo); // so use it
};

   Foo::Bar Foo::getBar(Foo foo) { return foo.bar; }
   
int main()
{
    Foo f, g;
    auto bar = f.getBar(g);
    (void) bar;
}