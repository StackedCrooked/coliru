struct Base {
    Base(int a) {}
};

struct Derived : Base {
    using Base::Base; // Inherit Base's constructors.
};

int main()
{
    Derived d(1);
}