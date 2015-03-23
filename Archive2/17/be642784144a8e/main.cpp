class Base {
public:
    Base(int) {}
};

class Derived : public Base {
public:
    Derived(int a)
    // uncomment to compile:
    //: Base(a)
    {}
};

int main(void) {}
