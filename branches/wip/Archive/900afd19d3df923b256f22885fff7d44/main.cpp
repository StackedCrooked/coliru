class C {
    int a = 5;
    int b = 6;
    friend class Proxy;
};

class Proxy {
    static int &getA(C &c) {return c.a;}
    friend class AAccessor;
};

struct AAccessor {
    C c;
    void foo() {
        Proxy::getA(c) = 6;
        //can't access b
    }
};

int main() {
    AAccessor access;
    access.foo();
}