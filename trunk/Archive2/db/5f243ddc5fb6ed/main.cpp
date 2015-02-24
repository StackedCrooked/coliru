struct FunctionalVoid {
    typedef void result_type;
    result_type foo () const { return; }
};

struct FunctionalInt {
    typedef int result_type;
    result_type foo () const { return 42; }
};

template< class F >
typename F::result_type
g (const F & f) {
   return f.foo ();
}

int main()
{
    FunctionalVoid obj1;
    g(obj1);
    
    FunctionalInt obj2;
    int result2 = g(obj2);
}
