struct A {
    using T = int;
};

struct B {
    using U = A;
    using V = void(U::T);
};
