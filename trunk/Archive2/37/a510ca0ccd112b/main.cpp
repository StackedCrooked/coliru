
    struct A; // incomplete type
    
    template<class T>
    struct D {
        T a;
        };
    
    template <class T>
    struct B { int * p = nullptr;  void operator -(const B&) const {}};
    
    int main() {
        B<D<A>> u, v;
        u - v;
    }