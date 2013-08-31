namespace w {
    template<class T>
    struct wrapper { T t; };
    
    template<class T> 
    T const& unwrap(T const& t) {
        return t;
    }
    
    template<class T>
    T const& unwrap(wrapper<T> const& w) {
        return w.t;
    }
    
    template<class T1,class T2>
    auto operator +(T1 t1, T2 t2) -> decltype(unwrap(t1)+unwrap(t2)) {
        return unwrap(t1)+unwrap(t2);
    }
    template<class T1,class T2>
    auto operator -(T1 t1, T2 t2) -> decltype(unwrap(t1)-unwrap(t2)) {
        return unwrap(t1)-unwrap(t2);
    }

    template<class T1,class T2>
    auto operator *(T1 t1, T2 t2) -> decltype(unwrap(t1)*unwrap(t2)) {
        return unwrap(t1)*unwrap(t2);
    }
}    

// Test case
struct test {};

test operator+(test const&, test const&) { return test(); }
test operator-(test const&, test const&) { return test(); }

int main() {
    test() + test();
    w::wrapper<test>() * w::wrapper<test>();
    return 0;
}
