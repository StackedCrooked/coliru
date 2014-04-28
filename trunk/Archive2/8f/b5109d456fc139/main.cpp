struct foo {
    int x() { return 0; }
    virtual int y() { return 1; }
};

int main () {
    foo f;
    
    int (foo::* nv)() = &foo::x;
    (f.*nv)();

    int (foo::* v)()  = &foo::y;
    (f.*v)();
}