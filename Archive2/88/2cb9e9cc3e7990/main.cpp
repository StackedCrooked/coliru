    struct A; // incomplete type
    
    template<class T>
    struct D { T d; };
    
    template <class T>
    struct B { int * p; };
    
    int main() {
        B<D<A>> u, v;
        u = v;  // doesn't compile; complain that D<A>::d has incomplete type
        u.operator=(v); // compiles
    }