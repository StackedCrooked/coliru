class A {
    public:
    A();
    ~A();
    const A& operator = (const A& rhs) {
        // assignment operations
        return *this;
    }
};

class B {
    public:
    B(const A a = A());
    ~B();
};

int main() {}