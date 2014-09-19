
    struct A; // incomplete type
    
    template<class T>
    struct D; // undefined
    
    template <class T>
    struct B { int * p; };
    
    int main() {
        B<D<A>> u, v;
        u = v;
        u.operator=(v); // compiles
    }