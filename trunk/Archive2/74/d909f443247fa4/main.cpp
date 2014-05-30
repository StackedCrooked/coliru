class A {
private:
    int a;
    friend class C;
};

class B : public A {};

class C {
    int test(B& b) { return b.a; }
};

int main()
{}
