struct base {
    base() {
        g();
    }
    
    virtual void f() = 0;
    
    void g() { f(); }
};

struct derived : base {
    void f() override {}
};

int main() {
    derived d;
}
