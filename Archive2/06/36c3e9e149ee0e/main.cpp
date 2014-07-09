struct A {

    int n;

    auto f() -> decltype(n) { // OK
        return n;
    }
};



struct B {

    auto f() -> decltype(n) { // error: 'n' was not declared in this scope
        return n;
    }

    int n;
};

int main() {

    return A().f() + B().f();
}