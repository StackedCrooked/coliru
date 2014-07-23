struct A {
    A() = default;
    A(A const&) = default; // copyable
    A& operator=(A const&) = default; // assignable
    A(A &&) = delete; // not movable
    A& operator=(A &&) = delete; // not movable
    ~A() = default;
};

template <typename T>
T& as_lvalue(T&& t) {
    return t;
}

A foo() {
     A a;
     return as_lvalue(a);
}

int main() {
    A a(as_lvalue(foo()));
    return 0;
}