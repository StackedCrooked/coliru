struct A {
    template <typename T>
    void operator=(T&&) && = delete; // no op= for rvalues

    // generate other special members normally
    A() = default;
    A(A const&) = default;
    A(A&&) = default;
    ~A() = default;
    // op= only for lvalues
    A& operator=(A&&) & = default;
    A& operator=(A const&) & = default;
};

int main() {
 A a;
 a = A(); // fine
 A() = A(); // error
 return 0; 
}