template <typename Derived>
struct base {
    base() {
        Derived* d = static_cast<Derived*>(this);
        d->foo = 42;
    }
};

struct derived : base<derived> {
    int foo;
};

int main() {
    derived d;    
}